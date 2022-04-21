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
	_actionName = NSNameAction::FlyTo;
	_actionType = EActionType::EACT_FlyTo;

	_bInstantAction = false;
	_bUpdateDestination = true;
}

void UActionFlyTo::VTMExecute()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

	if (_GetDestination(_destination) == false)
	{
		SetActionProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Destination Data"))
	}

	_myMovementComp = Cast<UMyCharacterMovementComponent>
		(GetActionOwner()->GetComponentByClass(UMyCharacterMovementComponent::StaticClass()));
	if (_myMovementComp == nullptr)
	{
		SetActionProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Movement component"))
	}

	if (GetStatusComp() == nullptr)
	{
		SetActionProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: no Status Component"))
	}

	if (GetStatusComp()->GetFinalValue(EStatusType::EStatus_FlyingSpeed) == 0.0f)
	{
		SetActionProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: Flying speed is zero"))
	}
}

void UActionFlyTo::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	FVector curLocation = GetActionOwner()->GetActorLocation();
	float dist = FVector::Distance(_destination, curLocation); 
	float distXY = FVector::DistXY(_destination, curLocation);

	//action completed
	//-------------------------------------------------------------------------------------------------------------
	if (dist < 300.0f)
	{
		//GetActionOwner()->GetCharacterMovement()->Velocity = FVector::ZeroVector;
		SetActionProcessSucceed();
	}


	//Get flying abilidy
	//-------------------------------------------------------------------------------------------------------------
	FFlyingAbilityData& flyingAbility = _myMovementComp->getFlyingAbilityData();

	FVector curVelocity = GetActionOwner()->GetVelocity();
	FVector newVelocity = curVelocity;

	FRotator curRotation = GetActionOwner()->GetActorRotation();
	FRotator newRotation = curRotation;

	//Destination
	//-------------------------------------------------------------------------------------------------------------
	FVector offset_Dest = _destination - curLocation;
	FVector dirToDest = offset_Dest.GetSafeNormal();
	FVector dirToDestXY = FVector(dirToDest.X, dirToDest.Y, 0.0f);
	dirToDestXY.Normalize();

	FVector actorForwardXY = GetActionOwner()->GetActorForwardVector();
	actorForwardXY.Z = 0;
	actorForwardXY.Normalize();
	
	float speedXY = curVelocity.Size2D();
	

	//delta yaw
	//-------------------------------------------------------------------------------------------------------------
	float deltaAngleDegreeXY_Forward_ToDest = FMath::FindDeltaAngleDegrees(actorForwardXY.Rotation().Yaw, dirToDestXY.Rotation().Yaw);

	float deltaYaw = ComputeDeltaYaw(speedXY, flyingAbility, deltaAngleDegreeXY_Forward_ToDest, deltaTime);

	newRotation.Yaw += deltaYaw;

	//SpeedXY
	//-------------------------------------------------------------------------------------------------------------
	float newspeedXY = ComputeSpeedXY(speedXY, flyingAbility, deltaAngleDegreeXY_Forward_ToDest, distXY, deltaTime);

	newVelocity = actorForwardXY * newspeedXY;

	//SpeedZ
	//-------------------------------------------------------------------------------------------------------------
	float newspeedZ = ComputeSpeedZ(curVelocity, flyingAbility, curLocation.Z, deltaTime);
	
	newVelocity.Z = newspeedZ;

	//apply new velocity, Rotation
	//-------------------------------------------------------------------------------------------------------------

	GetActionOwner()->SetActorRotation(newRotation);
	_myMovementComp->Velocity = newVelocity;


	//debug message
	//-------------------------------------------------------------------------------------------------------------

	DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), _destination, FColor::Black, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), GetActionOwner()->GetActorLocation() + GetActionOwner()->GetActorForwardVector() * 750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(dist));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "current Velocity: " + FString::SanitizeFloat(curVelocity.Size()));
}

bool UActionFlyTo::_GetDestination(FVector& outVector)
{
	return GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_DestLocation, outVector);
}


float UActionFlyTo::ComputeDeltaYaw(float curflyingSpeedXY, FFlyingAbilityData& flyingAbility, float deltaAngleDegreeXY_Forward_ToDest, float deltaTime)
{
	if (FMath::IsNearlyZero(deltaAngleDegreeXY_Forward_ToDest))
	{
		return 0.0f;
	}

	//Compute Track Radius,TrackCenter 
	//-------------------------------------------------------------------------------------------------------------
	FVector actorLocation = GetActionOwner()->GetActorLocation();
	FVector dirRight = GetActionOwner()->GetActorRightVector();
	dirRight.Z = 0;
	dirRight.Normalize();


	float trackRadius = curflyingSpeedXY / FMath::DegreesToRadians(flyingAbility.YawRate);
	FVector trackCenter = deltaAngleDegreeXY_Forward_ToDest < 0
		? actorLocation - dirRight * trackRadius : actorLocation + dirRight * trackRadius;

	float dist_Dest_TrackCenter = UMyGameplayStatics::ComputeDistance(_destination, trackCenter, EPlane::Plane_XY);


	if (dist_Dest_TrackCenter < trackRadius)
	{
		return 0.0f;
	}
	float deltaYawStep = flyingAbility.YawRate * deltaTime;
	float deltaYaw = deltaAngleDegreeXY_Forward_ToDest > 0 ?
		FMath::Min(deltaYawStep, deltaAngleDegreeXY_Forward_ToDest) : FMath::Max(-deltaYawStep, deltaAngleDegreeXY_Forward_ToDest);

	return deltaYaw;
}

float UActionFlyTo::ComputeSpeedXY(float curflyingSpeedXY, FFlyingAbilityData& flyingAbility, float deltaAngleDegreeXY_Forward_ToDest, float distXY, float deltaTime)
{
	if (FMath::IsNearlyZero(deltaAngleDegreeXY_Forward_ToDest))
	{
		return FMath::Min(curflyingSpeedXY + flyingAbility.AccelXY * deltaTime, flyingAbility.SpeedXYMax);
	}
	else
	{
		//s = v0t + 1/2 * at^2
		float time_decelerate = curflyingSpeedXY / flyingAbility.AccelXY;
		float distance_decelerate = curflyingSpeedXY * time_decelerate - flyingAbility.AccelXY * time_decelerate * time_decelerate * 0.5;

		if (distXY > distance_decelerate)
		{
			return FMath::Min(curflyingSpeedXY + flyingAbility.AccelXY * deltaTime, flyingAbility.SpeedXYMax);
		}
		else
		{
			return FMath::Max(curflyingSpeedXY - flyingAbility.AccelXY * deltaTime, 0.0f);
		}
	}
}

float UActionFlyTo::ComputeSpeedZ(FVector& curVelocity, FFlyingAbilityData& flyingAbility, float curAltitude, float deltaTime)
{
	float curSpeed_Z = FMath::Abs(curVelocity.Z);

	float offset_Z = _destination.Z - curAltitude;
	float altitude_diff = FMath::Abs(offset_Z);

	if (curVelocity.Z >= 0)
	{
		if (offset_Z < 0)
		{
			return curVelocity.Z - flyingAbility.AccelZ * deltaTime;
		}
		else
		{
			float time_decelerate = FMath::Abs(curSpeed_Z / flyingAbility.AccelZ);

			//s = v0t + 1/2 * at^2
			float distance_decelerate = curSpeed_Z * time_decelerate - flyingAbility.AccelZ * time_decelerate * time_decelerate * 0.5;

			if (altitude_diff > distance_decelerate)
			{
				return FMath::Min(curVelocity.Z + flyingAbility.AccelZ * deltaTime, flyingAbility.SpeedZMax);
			}
			else
			{
				return FMath::Max(curVelocity.Z - flyingAbility.AccelZ * deltaTime, 0.0f);
			}
		}
	}

	else /*if (curVelocity.Z < 0)*/
	{
		if (offset_Z > 0)
		{
			return curSpeed_Z - flyingAbility.AccelZ * deltaTime;
		}
		else
		{
			float time_decelerate = FMath::Abs(curSpeed_Z / flyingAbility.AccelZ);

			//s = v0t + 1/2 * at^2
			float distance_decelerate = curSpeed_Z * time_decelerate - flyingAbility.AccelZ * time_decelerate * time_decelerate * 0.5;

			if (altitude_diff > distance_decelerate)
			{
				return FMath::Max(curVelocity.Z - flyingAbility.AccelZ * deltaTime, -flyingAbility.SpeedZMax);
			}
			else
			{
				return FMath::Min(curVelocity.Z + flyingAbility.AccelZ * deltaTime, 0.0f);
			}
		}
	}
}