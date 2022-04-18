// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameSystem/MyGameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/MyCharacterMovementComponent.h"
#include "AIController.h"


UActionFlyTo::UActionFlyTo()
{
	_actionName = ActionName::FlyTo;
	_actionType = EActionType::EACT_FlyTo;


	_bInstantAction = false;
	_turnningSpeed = 500;

	_bUpdateDestination = true;

	//Roll
	_limitedRollDegree = 80.0f;
	_limitedPitchDegree = 80.0f;
	_yawDegreePerSecond = 90;
	_pitchDegreePerSecond = 10;
	_rollDegreePerSecond = -30;
	_resetFactor = 0;
	_resetFactorSpeed = 0.5f;
}

void UActionFlyTo::VTMExecute()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

	UMyCharacterMovementComponent* movementComp
		= Cast<UMyCharacterMovementComponent>(GetActionOwner()->GetMovementComponent());

	if (_GetDestination(_destination) == false || movementComp == false)
	{
		SetActionProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Destination Data"))
	}

	if (GetStatusInterface() == false)
	{
		SetActionProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Destination Data"))
	}

	if (GetStatusInterface()->VGetFinalValue(EStatusType::EStatus_FlyingSpeed) == 0.0f)
	{
		SetActionProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: Flying speed is zero"))
	}
}

void UActionFlyTo::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	FVector curLocation = GetActionOwner()->GetActorLocation();
	float distance = (_destination - curLocation).Size();

	//action completed
	//-------------------------------------------------------------------------------------------------------------
	if (distance < 10.0f)
	{
		SetActionProcessSucceed();
	}


	float flyingSpeedMax = GetStatusInterface()->VGetFinalValue(EStatusType::EStatus_FlyingSpeed);
	FVector curVelocity = GetActionOwner()->GetVelocity();
	FVector newVelocity = curVelocity;

	FRotator curRotation = GetActionOwner()->GetActorRotation();
	FRotator newRotation = curRotation;
	
	//Destination
	//-------------------------------------------------------------------------------------------------------------
	FVector offset_Dest = _destination - curLocation;
	FVector dirToDest = offset_Dest.GetSafeNormal();
	FVector dirToDest_XY = FVector(dirToDest.X, dirToDest.Y, 0.0f);
	

	if (curRotation.Yaw == dirToDest_XY.Rotation().Yaw) 
	{
		
	}

	else
	{



	}



	//delta yaw
	float deltaYaw = ComputeDeltaYaw(flyingSpeedMax, dirToDest, GetActionOwner()->GetActorForwardVector(), deltaTime);
	newRotation.Yaw += deltaYaw;

	//Pitch
	//-------------------------------------------------------------------------------------------------------------
	
	float acceleration = 250.0f;
	float curSpeed_Z = FMath::Abs(curVelocity.Z);

	float finalVelocity_Z = 0;
	float altitude_diff = FMath::Abs(_destination.Z - curLocation.Z);


	if (curVelocity.Z >= 0)
	{
		if (offset_Dest.Z < 0)
		{
			finalVelocity_Z = curVelocity.Z - acceleration * deltaTime;
		}
		else
		{
			float time_decelerate = FMath::Abs(curSpeed_Z / acceleration);

			//s = v0t + 1/2 * at^2
			float distance_decelerate = curSpeed_Z * time_decelerate - acceleration * time_decelerate * time_decelerate * 0.5;
			
			if (altitude_diff > distance_decelerate)
			{
				finalVelocity_Z = FMath::Min(curVelocity.Z + acceleration * deltaTime, flyingSpeedMax);
			}
			else
			{
				finalVelocity_Z = FMath::Max(curVelocity.Z - acceleration * deltaTime, 0.0f);
			}
		}
	}

	else /*if (curVelocity.Z < 0)*/
	{
		if (offset_Dest.Z > 0)
		{
			finalVelocity_Z = curSpeed_Z - acceleration * deltaTime;
		
		}
		else
		{
			float time_decelerate = FMath::Abs(curSpeed_Z / acceleration);

			//s = v0t + 1/2 * at^2
			float distance_decelerate = curSpeed_Z * time_decelerate - acceleration * time_decelerate * time_decelerate * 0.5;

			if (altitude_diff > distance_decelerate)
			{
				finalVelocity_Z = FMath::Max(curVelocity.Z - acceleration * deltaTime, -flyingSpeedMax);
			}
			else
			{
				finalVelocity_Z = FMath::Min(curVelocity.Z + acceleration * deltaTime, 0.0f);
			}
		}
	}

	//apply 
	GetActionOwner()->SetActorRotation(newRotation);
	GetActionOwner()->GetMovementComponent()->Velocity = GetActionOwner()->GetActorForwardVector() * 1000;
	GetActionOwner()->GetMovementComponent()->Velocity.Z = finalVelocity_Z;


	//debug message
	//-------------------------------------------------------------------------------------------------------------
	DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), GetActionOwner()->GetActorLocation() + GetActionOwner()->GetActorForwardVector() * 750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(distance));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "current Velocity: " + FString::SanitizeFloat(curVelocity.Size()));
}

bool UActionFlyTo::_GetDestination(FVector& outVector)
{
	return GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_DestLocation, outVector);
}


float UActionFlyTo::ComputeDeltaYaw(float flyingSpeed, FVector dirToDestination, FVector dirForward, float deltaTime)
{
	//Direction to Destination
	dirToDestination.Z = 0;
	dirToDestination.Normalize();

	//Direction Forward
	dirForward.Z = 0;
	dirForward.Normalize();


	//compute delta Degree 
	float currentYaw = dirForward.Rotation().Yaw;
	float destYaw = dirToDestination.Rotation().Yaw;
	float angle_Forward_ToDest = FMath::FindDeltaAngleDegrees(currentYaw, destYaw);

	float deltaYaw = _yawDegreePerSecond * deltaTime;
	if (angle_Forward_ToDest < 0) deltaYaw = -deltaYaw;

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "angleBetween_Front_ToDest: " + FString::SanitizeFloat(angle_Forward_ToDest));



	//float distanceFromCurLocToDest= 

	//Compute Track Radius,TrackCenter 
	//-------------------------------------------------------------------------------------------------------------
	float trackRadius = flyingSpeed / FMath::DegreesToRadians(_yawDegreePerSecond);
	FVector dirRight = GetActionOwner()->GetActorRightVector();
	dirRight.Z = 0;
	dirRight.Normalize();
	FVector trackCenter = angle_Forward_ToDest < 0
		? GetActionOwner()->GetActorLocation() - dirRight * trackRadius
		: GetActionOwner()->GetActorLocation() + dirRight * trackRadius;

	float distance_Dest_TrackCenter = UMyGameplayStatics::ComputeDistance(_destination, trackCenter, EPlane::Plane_XY);

	float resultDeltaYaw = deltaYaw;

	if (distance_Dest_TrackCenter < trackRadius)
	{
		resultDeltaYaw = 0;
	}

	else if (FMath::Abs(angle_Forward_ToDest) < 0.001f)
	{
		resultDeltaYaw = 0;
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, "turned to completed ");
	}
	else
	{
		float angle_Forward_ToDest_AfterRotation = angle_Forward_ToDest - deltaYaw;

		if (deltaYaw > 0 && angle_Forward_ToDest_AfterRotation < 0)
		{
			resultDeltaYaw = deltaYaw - angle_Forward_ToDest_AfterRotation;
		}

		else if (deltaYaw < 0 && angle_Forward_ToDest_AfterRotation > 0)
		{
			resultDeltaYaw = deltaYaw - angle_Forward_ToDest_AfterRotation;
		}
	}

	//debug message
	//DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), trackCenter, FColor::Emerald, false, -1.0f, 0U, 30.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Circle Center: " + (circleCenter).ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("Turnning Radius: ") + FString::SanitizeFloat(turningRadius));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("DistanceToCircleCenter ") + FString::SanitizeFloat(distanceFronDestLocToCircleCenter));
	DrawDebugCircle(GetWorld(), trackCenter, trackRadius, 1, FColor::Green);
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "currevtYaw: " + FString::SanitizeFloat(currentYaw));
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "DestYaw: " + FString::SanitizeFloat(destYaw));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "DeltaYaw: " + FString::SanitizeFloat(resultDeltaYaw));

	return resultDeltaYaw;
}

float UActionFlyTo::ComputeVerticalSpeed()
{
	float offset = 0;

	float speedMax = 3200.0f;
	float acceleration = 10.0f;
	float curSpeed = 10.0f;
	float deltaTime = 0.0f;

	float time_decelerate = curSpeed / acceleration;

	//s = v0t + 1/2 * at^2
	float distance_decelerate = curSpeed * time_decelerate - acceleration * time_decelerate * time_decelerate * 0.5;

	if (offset > distance_decelerate)
	{
		return FMath::Min(curSpeed + acceleration * deltaTime, speedMax);
	}

	else
	{
		return FMath::Max(curSpeed - acceleration * deltaTime, 0.0f);
	}
}

float UActionFlyTo::ComputePitch()
{
	float pitchLimit = FMath::DegreesToRadians(50);
	float pitchSpeed = FMath::DegreesToRadians(10);
	float speed = 500;
	float altitudeOffset = 1000;

	float timeToMaxSpeed = pitchLimit / pitchSpeed;

	//w: angular velocity
	//v: vertical velocity
	//A: altitude Offset
	// -----------------------------------
	//=> v = speed * sin(w * t);
	//=> integral: -cos(w * t) / w
	//=> S(0,t) : (1 - cos(w *t) )/w
	//=>  ((1 - cos(w *t) )/w) * 2 = A
	//=> t = arccos((2 - aw)/2) / w 

	//compute max distanceTraveled during pitch
	//Definite Integral: S(0,PitchLimit) sin(pitchLimit)
	// 
	// 
	//(-cos(wt)+1)/w * speed;
	float distanceTraveledDuringPitchMax = 2 * speed * (-FMath::Cos(pitchLimit) + 1) / pitchSpeed;

	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "Pitch Travel: " + FString::SanitizeFloat(distanceTraveledDuringPitchMax));


	float maxSpeed = speed * FMath::Sin(pitchLimit);

	if (altitudeOffset > distanceTraveledDuringPitchMax)
	{
		return (altitudeOffset - distanceTraveledDuringPitchMax) / timeToMaxSpeed;
	}
	else
	{
		//w: angular velocity
		//v: vertical velocity
		//A: Target altitude
		// -----------------------------------
		//=> v = sin(w * t);
		//=> integral: -cos(w * t) / w
		//=> S(0,t) : (1 - cos(w *t) )/w
		//=>  ((1 - cos(w *t) )/w) * 2 = A
		//=> t = arccos((2 - aw)/2) / w 

		return FMath::Acos((2 - altitudeOffset * pitchSpeed) / 2) / pitchSpeed;
	}

}