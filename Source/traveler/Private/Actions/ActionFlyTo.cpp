// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameSystem/MyGameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Components/StatusComponent.h"
#include "AIController.h"


UActionFlyTo::UActionFlyTo()
{
	_processName = NSNameAction::FlyTo;
	_actionType = EActionType::EACT_Flying;

	_bIsInstantProcess = false;
	_bUpdateDestination = true;
}



bool UActionFlyTo::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	
	_myMovementComp = Cast<UMyCharacterMovementComponent>
		(GetActionOwner()->GetComponentByClass(UMyCharacterMovementComponent::StaticClass()));
	if (_myMovementComp == nullptr)
	{
		UE_LOG(LogAction, Warning, TEXT("Fly to: No My Movement component"));
		return false;
	}
	else
	{
		if (_myMovementComp->MovementMode != EMovementMode::MOVE_Flying) return false;
		if (_myMovementComp->GetMaxSpeed() == 0.0f) return false;
	}

	return true;
}

void UActionFlyTo::VOnExecute()
{
	Super::VOnExecute();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

	if (!TryGetRequiredData())
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Destination Data"));
	}
}

void UActionFlyTo::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	if (!TryGetRequiredData())
	{
		SetProcessFailed();
	}

	FVector curLocation = GetActionOwner()->GetActorLocation();
	FRotator curRotation = GetActionOwner()->GetActorRotation();
	float dist = FVector::Distance(_destLocation, curLocation);
	float distXY = FVector::DistXY(_destLocation, curLocation);
	float distZ = FMath::Abs(_destAltitude - curLocation.Z);

	//forward planeXY
	FVector actorForwardXY = GetActionOwner()->GetActorForwardVector();
	FRotator forwardRot = GetActionOwner()->GetActorForwardVector().Rotation();

	actorForwardXY.Z = 0;
	actorForwardXY.Normalize();

	//dest direction PlaneXY
	FVector offset_Dest = _destLocation - curLocation;
	FVector dirToDest = offset_Dest.GetSafeNormal();
	FVector dirToDestXY = FVector(dirToDest.X, dirToDest.Y, 0.0f);
	dirToDestXY.Normalize();

	//angle degree between forward with dest
	float deltaAngleH_Forward_ToDest = FMath::FindDeltaAngleDegrees(actorForwardXY.Rotation().Yaw, dirToDestXY.Rotation().Yaw);
	//float deltaAngleDegreeV_Forward_ToDest = FMath::FindDeltaAngleDegrees(actorForwardXY.Rotation().Pitch, dirToDestXY.Rotation().Pitch);
	
	//action completed
	//-------------------------------------------------------------------------------------------------------------

	float tolerance = _myMovementComp->GetMaxSpeed() * deltaTime * 2.0f;

	if (FMath::Abs(distXY - _keepingDistanceXY) <= tolerance
		&& distZ < tolerance
		&& (_bFaceToDest == false || FMath::Abs(deltaAngleH_Forward_ToDest) < 1.0f)
		&& FMath::Abs(curRotation.Pitch) < 1.0f
		&& FMath::Abs(curRotation.Roll) < 1.0f)
	{
		if (_bBrakeAtDest)
		{
			//GetActionOwner()->GetCharacterMovement()->StopMovementImmediately();
		}
		SetProcessSucceed();
	}

	//Get flying abiliyy
	//-------------------------------------------------------------------------------------------------------------
	FFlyingAbilityData& flyingAbility = _myMovementComp->getFlyingAbilityData();
	FVector curVelocity = GetActionOwner()->GetVelocity();


	//Yaw Rotation  
	//-------------------------------------------------------------------------------------------------------------

	float curYawSpeed = _myMovementComp->GetCurrentYawSpeed();

	//Compute Track Radius
	//v = W * R => R = V / W 
	float trackRadius = curVelocity.Size2D() / FMath::DegreesToRadians((flyingAbility.YawAngSpeedMax))+3000;
	//float trackRadius = curVelocity.Size2D() / FMath::DegreesToRadians(curYawSpeed + 0.00001f);


	//Compute Track Center
	FVector dirRight = GetActionOwner()->GetActorRightVector();
	dirRight.Z = 0;
	dirRight.Normalize();

	FVector trackCenter = deltaAngleH_Forward_ToDest < 0
		? curLocation - dirRight * trackRadius : curLocation + dirRight * trackRadius;

	//Compute distance from trackcenter to destination
	float dist_TrackCenter_Dest = FVector::Dist2D(_destLocation, trackCenter);


	float distXY_Safe = FMath::Max(trackRadius, _keepingDistanceXY + tolerance);


	if (dist_TrackCenter_Dest < distXY_Safe)
	{
		_myMovementComp->RotateDeltaYaw(FMath::UnwindDegrees(deltaAngleH_Forward_ToDest + 180), deltaTime);
		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Move Out ");
	}
	else
	{
		_myMovementComp->RotateDeltaYaw(deltaAngleH_Forward_ToDest, deltaTime);
		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Move In");
	}

	//Pitch Rotation  
	//-------------------------------------------------------------------------------------------------------------
	float offset_Z = _destAltitude - curLocation.Z;
	float DistTraveledDuringKeepHorizontal = _myMovementComp->ComputeDistTraveledDuringPitch0();

	if (distZ < tolerance)
	{
		_myMovementComp->KeepHorizontal(deltaTime);
	}
	else
	{
		if (offset_Z > 0)
		{
			_myMovementComp->Ascend(DistTraveledDuringKeepHorizontal + curLocation.Z < _destAltitude, deltaTime);
		}
		else
		{
			_myMovementComp->Ascend(-DistTraveledDuringKeepHorizontal + curLocation.Z < _destAltitude, deltaTime);
		}
	}

	//Horizontal Movement  
	//-------------------------------------------------------------------------------------------------------------
		
	if (FMath::Abs(deltaAngleH_Forward_ToDest) > 1.0f)
	{
		_myMovementComp->Accelerate(true, deltaTime);
	}
	else if(_bBrakeAtDest)
	{
		float breakingDistance = _myMovementComp->ComputeBrakingDistance();

		if (distXY > breakingDistance)
		{
			_myMovementComp->Accelerate(true, deltaTime);
		}
		else
		{
			_myMovementComp->Accelerate(false, deltaTime);
		}
	}
	else
	{
		_myMovementComp->Accelerate(true, deltaTime);
	}

	//
	//debug message
	//-------------------------------------------------------------------------------------------------------------
	//DrawDebugLine(GetWorld(), curLocation, curLocation + 4000 * curVelocity.GetSafeNormal(), FColor::Blue, false, -1.0f, 0U, 30.0f);
	//DrawDebugLine(GetWorld(), curLocation, FVector(curLocation.X, curLocation.Y, _destAltitude), FColor::Blue, false, -1.0f, 0U, 30.0f);
	//DrawDebugLine(GetWorld(), curLocation, _destLocation, FColor::Black, false, -1.0f, 0U, 30.0f);
	//DrawDebugLine(GetWorld(), curLocation, FVector(_destLocation.X, _destLocation.Y, curLocation.Z), FColor::Black, false, -1.0f, 0U, 30.0f);
	//DrawDebugLine(GetWorld(), curLocation, curLocation + GetActionOwner()->GetActorForwardVector() * 750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(dist));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "current Velocity: " + FString::SanitizeFloat(curVelocity.Size()));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "z offset: " + FString::SanitizeFloat(offset_Z));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "current pitch: " + FString::SanitizeFloat(curRotation.Pitch));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "current Altitude: " + FString::SanitizeFloat(curLocation.Z));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "dest Altitude: " + FString::SanitizeFloat(_destAltitude));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "distance xy: " + FString::SanitizeFloat(distXY));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, "deltaAngleDegreeH_Forward_ToDest: " + FString::SanitizeFloat(deltaAngleDegreeH_Forward_ToDest));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "KeepDistanceXY: " + FString::SanitizeFloat(_keepingDistanceXY));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "distXY: " + FString::SanitizeFloat(distXY));
}

bool UActionFlyTo::TryGetRequiredData()
{
	if (GetActionBlackBoard()->TryGetData_FVector(NSActionData::DestLocation::Name, _destLocation) == false) 
	{
		return false;
	}

	_keepingDistanceXY = 0;
	GetActionBlackBoard()->TryGetData_Float(NSActionData::keepDistanceXY::Name, _keepingDistanceXY);

	_destAltitude = _destLocation.Z;
	GetActionBlackBoard()->TryGetData_Float(NSActionData::DestAltitude::Name, _destAltitude);

	_bFaceToDest = false;
	GetActionBlackBoard()->TryGetData_Bool(NSActionData::FaceToDest::Name, _bFaceToDest);

	_bBrakeAtDest = false;
	GetActionBlackBoard()->TryGetData_Bool(NSActionData::BrakeAtDest::Name, _bBrakeAtDest);

	return true;
}