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
	float deltaAngleDegreeH_Forward_ToDest = FMath::FindDeltaAngleDegrees(actorForwardXY.Rotation().Yaw, dirToDest.Rotation().Yaw);
	float deltaAngleDegreeV_Forward_ToDest = FMath::FindDeltaAngleDegrees(actorForwardXY.Rotation().Pitch, dirToDest.Rotation().Pitch);

	//action completed
	//-------------------------------------------------------------------------------------------------------------
	if (distXY < _destRadius && distZ < _destAltitude && FMath::Abs(deltaAngleDegreeH_Forward_ToDest) < 5.0f)
	{
		//GetActionOwner()->GetCharacterMovement()->Velocity = FVector::ZeroVector;
		SetProcessSucceed();
	}


	//Get flying abiliyy
	//-------------------------------------------------------------------------------------------------------------
	FFlyingAbilityData& flyingAbility = _myMovementComp->getFlyingAbilityData();
	FVector curVelocity = GetActionOwner()->GetVelocity();


	//Rotation Yaw 
	//-------------------------------------------------------------------------------------------------------------
	FRotator curRot = GetActionOwner()->GetActorRotation();
	FRotator newRot = curRot;

	float deltaYaw = 0.0f;
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
			deltaYaw = flyingAbility.YawAngSpeed * deltaTime;

			deltaYaw = deltaAngleDegreeH_Forward_ToDest > 0 ?
				FMath::Min(deltaYaw, deltaAngleDegreeH_Forward_ToDest)
				: FMath::Max(-deltaYaw, deltaAngleDegreeH_Forward_ToDest);
		}
	}

	//Rotation Pitch 
	//-------------------------------------------------------------------------------------------------------------
	float offset_Z = _destAltitude - curLocation.Z;
	float deltaPitch = flyingAbility.PitchAngSpeed * deltaTime;
	if (offset_Z > 0)
	{
		deltaPitch = FMath::Min(deltaPitch, flyingAbility.PitchLimit - curRot.Pitch);
	}
	else
	{
		deltaPitch = FMath::Max(-deltaPitch, -flyingAbility.PitchLimit - curRot.Pitch);
	}

	if (deltaYaw != 0.0f || deltaPitch != 0.0f)
	{
		newRot.Yaw += deltaYaw;
		newRot.Pitch += deltaPitch;
		GetActionOwner()->SetActorRotation(newRot);
	}

	//Movement Horizontal 
	//-------------------------------------------------------------------------------------------------------------
	if (FMath::IsNearlyZero(deltaAngleDegreeH_Forward_ToDest))
	{
		_myMovementComp->Accelerate(true, deltaTime);
	}
	else
	{
		float DistTraveledDuringDecelerateTo0 = _myMovementComp->ComputeDistTraveledDuringDecelerateTo0();

		if (distXY > DistTraveledDuringDecelerateTo0)
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

	DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), _destLocation, FColor::Black, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), GetActionOwner()->GetActorLocation() + GetActionOwner()->GetActorForwardVector() * 750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(dist));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "current Velocity: " + FString::SanitizeFloat(curVelocity.Size()));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "current Altitude: " + FString::SanitizeFloat(curLocation.Z));
}

bool UActionFlyTo::TryGetDestData()
{
	return GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_DestLocation, _destLocation) &&
		GetActionBlackBoard()->TryGetData_Float(EActionDataKey::EACTD_DestRadius, _destRadius) &&
		GetActionBlackBoard()->TryGetData_Float(EActionDataKey::EACTD_DestAltitude, _destAltitude);
}