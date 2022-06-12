// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/Character.h"
#include "GameSystem/MyGameplayStatics.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Components/StatusComponent.h"
#include "DrawDebugHelpers.h"

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

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

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
	//float distZ = FMath::Abs(_destAltitude - curLocation.Z);

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

	if (distXY > _keepingDistanceXY_Min && distXY < _keepingDistanceXY_Max
		&& curLocation.Z > _destAltitude_Min && curLocation.Z < _destAltitude_Max
		&& (_bFaceToDest == false || FMath::Abs(deltaAngleH_Forward_ToDest) < 1.0f)
		&& FMath::Abs(curRotation.Pitch) == 0.0f
		&& FMath::Abs(curRotation.Roll) < 1.0f)
	{
		if (_bBrakeAtDest)
		{
			GetActionOwner()->GetCharacterMovement()->StopMovementImmediately();
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


	float distXY_Safe = FMath::Max(trackRadius, _keepingDistanceXY_Max);


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


	//float offset_Z = _destAltitude - curLocation.Z;
	float DistTraveledDuringKeepHorizontal = _myMovementComp->ComputeDistTraveledDuringPitch0();

	if (curLocation.Z < _destAltitude_Min)
	{
		DistTraveledDuringKeepHorizontal + curLocation.Z > _destAltitude_Min ?
			_myMovementComp->Ascend(false, deltaTime) : _myMovementComp->Ascend(true, deltaTime);
	}
	else if (curLocation.Z > _destAltitude_Max)
	{
		DistTraveledDuringKeepHorizontal + curLocation.Z < _destAltitude_Max ?
			_myMovementComp->Ascend(true, deltaTime) : _myMovementComp->Ascend(false, deltaTime);
	}
	else
	{
		_myMovementComp->KeepHorizontal(deltaTime);
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
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "pitch: " + FString::SanitizeFloat(curRotation.Pitch));
}

bool UActionFlyTo::TryGetRequiredData()
{
	if (GetActionBlackBoard()->TryGetData_FVector(NSActionData::DestLocation::Name, _destLocation) == false) 
	{
		return false;
	}

	_keepingDistanceXY_Min= 0;
	GetActionBlackBoard()->TryGetData_Float(NSActionData::keepDistanceXY_Min::Name, _keepingDistanceXY_Min);

	_keepingDistanceXY_Max = 0;
	GetActionBlackBoard()->TryGetData_Float(NSActionData::keepDistanceXY_Max::Name, _keepingDistanceXY_Max);

	_destAltitude_Min = _destLocation.Z;
	GetActionBlackBoard()->TryGetData_Float(NSActionData::DestAltitude_Min::Name, _destAltitude_Min);

	_destAltitude_Max = _destLocation.Z;
	GetActionBlackBoard()->TryGetData_Float(NSActionData::DestAltitude_Max::Name, _destAltitude_Max);

	_bFaceToDest = false;
	GetActionBlackBoard()->TryGetData_Bool(NSActionData::FaceToDest::Name, _bFaceToDest);

	_bBrakeAtDest = false;
	GetActionBlackBoard()->TryGetData_Bool(NSActionData::BrakeAtDest::Name, _bBrakeAtDest);

	return true;
}