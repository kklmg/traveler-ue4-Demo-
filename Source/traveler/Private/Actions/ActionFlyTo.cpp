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

	_horizontalTolerance = 1500.0f;
	_verticalTolerance = 1500.0f;
}



bool UActionFlyTo::VTMCanExecute()
{
	if (!Super::VTMCanExecute()) return false;
	//
	//
	//
	return true;
}

void UActionFlyTo::VTMExecute()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

	if (!TryGetDestData())
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Destination Data"));
	}

	_myMovementComp = Cast<UMyCharacterMovementComponent>
		(GetActionOwner()->GetComponentByClass(UMyCharacterMovementComponent::StaticClass()));
	if (_myMovementComp == nullptr)
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Movement component"));
	}

	if (GetStatusComp() == nullptr)
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: no Status Component"));
	}

	if (GetStatusComp()->GetFinalValue(EStatusType::EStatus_FlyingSpeed) == 0.0f)
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: Flying speed is zero"));
	}
}

void UActionFlyTo::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	if (!TryGetDestData())
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
	float deltaAngleDegreeH_Forward_ToDest = FMath::FindDeltaAngleDegrees(actorForwardXY.Rotation().Yaw, dirToDestXY.Rotation().Yaw);
	//float deltaAngleDegreeV_Forward_ToDest = FMath::FindDeltaAngleDegrees(actorForwardXY.Rotation().Pitch, dirToDestXY.Rotation().Pitch);

	//action completed
	//-------------------------------------------------------------------------------------------------------------

	if (distXY < _destRadius + _horizontalTolerance 
		&& distZ < _verticalTolerance 
		&& FMath::Abs(deltaAngleDegreeH_Forward_ToDest) < 2.0f 
		&& FMath::Abs(curRotation.Pitch) < 2.0f)
	{
		//GetActionOwner()->GetCharacterMovement()->StopMovementImmediately();
		SetProcessSucceed();
	}

	//Get flying abiliyy
	//-------------------------------------------------------------------------------------------------------------
	FFlyingAbilityData& flyingAbility = _myMovementComp->getFlyingAbilityData();
	FVector curVelocity = GetActionOwner()->GetVelocity();


	//Rotation Yaw 
	//-------------------------------------------------------------------------------------------------------------

	if (FMath::IsNearlyZero(deltaAngleDegreeH_Forward_ToDest) == false)
	{
		//Compute Track Radius
		//v = W * R => R = V / W 
		float trackRadius = curVelocity.Size2D() / FMath::DegreesToRadians(flyingAbility.YawAngSpeed);

		//Compute Track Center
		FVector dirRight = GetActionOwner()->GetActorRightVector();
		dirRight.Z = 0;
		dirRight.Normalize();

		FVector trackCenter = deltaAngleDegreeH_Forward_ToDest < 0
			? curLocation - dirRight * trackRadius : curLocation + dirRight * trackRadius;

		//Compute distance from trackcenter to destination
		float dist_TrackCenter_Dest = FVector::Dist2D(_destLocation, trackCenter);


		if (dist_TrackCenter_Dest > trackRadius && curVelocity.Size2D() > 50.0f)
		{
			_myMovementComp->RotateToYaw(deltaAngleDegreeH_Forward_ToDest,deltaTime);
		}
	}

	//float tolerance;

	//Rotation Pitch 
	//-------------------------------------------------------------------------------------------------------------
	float offset_Z = _destAltitude - curLocation.Z;
	float DistTraveledDuringKeepHorizontal = _myMovementComp->ComputeDistTraveledDuringPitch0();

	if (distZ < _verticalTolerance)
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

	//Movement Horizontal 
	//-------------------------------------------------------------------------------------------------------------
	if (FMath::IsNearlyZero(deltaAngleDegreeH_Forward_ToDest))
	{
		_myMovementComp->Accelerate(true, deltaTime);
	}
	else
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

	//debug message
	//-------------------------------------------------------------------------------------------------------------
	//DrawDebugLine(GetWorld(), curLocation, FVector(curLocation.X, curLocation.Y, _destAltitude), FColor::Blue, false, -1.0f, 0U, 30.0f);
	//DrawDebugLine(GetWorld(), curLocation, _destLocation, FColor::Black, false, -1.0f, 0U, 30.0f);
	//DrawDebugLine(GetWorld(), curLocation, FVector(_destLocation.X, _destLocation.Y, curLocation.Z), FColor::Black, false, -1.0f, 0U, 30.0f);
	//DrawDebugLine(GetWorld(), curLocation, curLocation + GetActionOwner()->GetActorForwardVector() * 750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	/*GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(dist));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "current Velocity: " + FString::SanitizeFloat(curVelocity.Size()));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "z offset: " + FString::SanitizeFloat(offset_Z));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "current pitch: " + FString::SanitizeFloat(curRotation.Pitch));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "current Altitude: " + FString::SanitizeFloat(curLocation.Z));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "dest Altitude: " + FString::SanitizeFloat(_destAltitude));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "distance xy: " + FString::SanitizeFloat(distXY));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "dest Radius: " + FString::SanitizeFloat(_destRadius));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, "deltaAngleDegreeH_Forward_ToDest: " + FString::SanitizeFloat(deltaAngleDegreeH_Forward_ToDest));*/

}

bool UActionFlyTo::TryGetDestData()
{
	return GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_DestLocation, _destLocation) &&
		GetActionBlackBoard()->TryGetData_Float(EActionDataKey::EACTD_DestRadius, _destRadius) &&
		GetActionBlackBoard()->TryGetData_Float(EActionDataKey::EACTD_DestAltitude, _destAltitude);
}