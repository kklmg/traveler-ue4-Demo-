// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameSystem/MyBlueprintFunctionLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/MyCharacterMovementComponent.h"


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
	_yawDegreePerSecond = 25;
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
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Destination Setted"))
		SetActionProcessFailed();
		return;
	}
	movementComp->GenerateFlyingUpSimulationData(_destination.Z);
}

void UActionFlyTo::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	//Update Destination
	//-------------------------------------------------------------------------------------------------------------
	if(_bUpdateDestination)
	{
		if (_GetDestination(_destination))
		{
			UE_LOG(LogAction, Warning, TEXT("Fly to: No Destination Setted"))
		}
		else
		{
			SetActionProcessFailed();
			return;
		}
	}

	//Get Flying Speed
	//-------------------------------------------------------------------------------------------------------------
	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	float flyingSpeed = character->GetCharacterMovement()->MaxFlySpeed;


	//Current Transform State
	//-------------------------------------------------------------------------------------------------------------
	FTransform curTransform = GetActionOwner()->GetActorTransform();
	FVector curLocation = curTransform.GetLocation();
	FQuat curQuat = curTransform.GetRotation();
	FRotator curRotator = curQuat.Rotator();

	FVector actorForward = character->GetActorForwardVector();
	FVector upVector = character->GetActorUpVector();
	FVector rightVector = character->GetActorRightVector();


	//Get Actor Bounds
	

	//Destination
	//-------------------------------------------------------------------------------------------------------------
	FVector dirToDestination = _destination - curLocation;
	FVector destLocXY(_destination.X, _destination.Y, curLocation.Z);
	float distance = (_destination - curLocation).Size();

	//get actor bounds
	FVector outOrigin;
	FVector outBoxExtent;
	character->GetActorBounds(true, outOrigin, outBoxExtent);

	//debug message
	DrawDebugLine(GetWorld(), curLocation, _destination, FColor::Red, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), curLocation, destLocXY, FColor::Green, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), GetActionOwner()->GetActorLocation() + actorForward * 750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(distance));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Velocity: " + FString::SanitizeFloat((character->GetVelocity()).Size()));

	//Check Is at destination
	//-------------------------------------------------------------------------------------------------------------
	if (distance < 1000)
	{
		if(_resetFactor == 1.0f)
		{
			SetActionProcessSucceed();
			_resetFactor = 0;
			return;
		}
		else
		{	
			_resetFactor += _resetFactorSpeed * deltaTime;

			_resetFactor=FMath::Clamp(_resetFactor,0.0f,1.0f);

			FRotator standard(0,curRotator.Yaw, 0);
			FQuat quat = FQuat::Slerp(curQuat, standard.Quaternion(), _resetFactor);
			character->SetActorRotation(quat);

			return;
		}
	}


	FRotator newRotation = actorForward.Rotation();
	FVector newForwardVector = actorForward;


	//Yaw
	//-------------------------------------------------------------------------------------------------------------
	float deltaYaw = _YawTurnning(flyingSpeed,dirToDestination, actorForward, deltaTime);
	newRotation.Yaw += deltaYaw;


	//Pitch
	//-------------------------------------------------------------------------------------------------------------
	float altitudeOffset = _destination.Z - curLocation.Z;

	float verticalSpeed = actorForward.Z * flyingSpeed;
	float verticalStep = verticalSpeed * deltaTime;

	FRotator forward_Rotator = actorForward.Rotation();

	float breakingDistance = 0; 

	
	float pitchStep = _pitchDegreePerSecond * deltaTime;


	//forward_Rotator.Pitch += pitchStep;

	//FVector forwardArfterPitch = forward_Rotator.Vector().GetSafeNormal();

	//float afterAltitude = forwardArfterPitch.Z * flyingSpeed;


	

	//float verticalStepMax = _pitchDegreePerSecond * deltaTime;

	



	//if(verticalStep > altitudeOffset)
	//{
	//	deltaPitch = _pitchDegreePerSecond 
	//
	//
	//}

	
	float deltaPitch = _pitchDegreePerSecond * deltaTime;
	



	//float verticalSpeed = _flyingSpeed * FMath::Sin(curPitch);
	//float HorizontalSpeed = _flyingSpeed * FMath::Cos(curPitch);

	//float s = curPitch / _pitchDegreePerSecond;
	//float d = verticalSpeed

	//if(heightOffset)

	GetBreakingDistance_Z(altitudeOffset, forward_Rotator.Pitch, _pitchDegreePerSecond);



	float pitchAfterRotation = 0;
	if (FMath::Abs(altitudeOffset) < 100)
	{
		if (forward_Rotator.Pitch == 0)
		{
			deltaPitch = 0;
		}
		else
		{
			deltaPitch = -forward_Rotator.Pitch;
		}
	}
	else
	{
		if (altitudeOffset < 0)
		{
			deltaPitch = -deltaPitch;
		}
		pitchAfterRotation = forward_Rotator.Pitch + deltaPitch;
		pitchAfterRotation = FMath::Clamp(pitchAfterRotation, -_limitedPitchDegree, _limitedPitchDegree);

		deltaPitch = pitchAfterRotation - forward_Rotator.Pitch;
	}


	newRotation.Pitch += deltaPitch;
	newForwardVector = newRotation.Vector();


	FQuat turnQuat = FQuat::FindBetween(actorForward,newForwardVector);

	//apply movement
	//-------------------------------------------------------------------------------------------------------------
	character->AddActorWorldRotation(turnQuat);
	character->AddMovementInput(actorForward);
	
}

bool UActionFlyTo::_GetDestination(FVector& outVector)
{
	return GetActionBlackBoard()->TryGetData_FVector(EActionDataKey::EACTD_DestLocation, outVector);
}


float UActionFlyTo::_YawTurnning(float flyingSpeed,FVector dirToDestination, FVector dirForward, float deltaTime)
{
	//-------------------------------------------------------------------------------------------------------------
	//Direction to Destination
	dirToDestination.Z = 0;
	dirToDestination.Normalize();

	//Direction Forward
	dirForward.Z = 0;
	dirForward.Normalize();


	//compute delta Degree 
	float currentYaw = dirForward.Rotation().Yaw;
	float destYaw = dirToDestination.Rotation().Yaw;
	float angle_Forward_ToDest = FMath::FindDeltaAngleDegrees(currentYaw,destYaw);

	float deltaYaw = _yawDegreePerSecond * deltaTime;
	if (angle_Forward_ToDest < 0) deltaYaw = -deltaYaw;

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "angleBetween_Front_ToDest: " + FString::SanitizeFloat(angle_Forward_ToDest));


	
	//float distanceFromCurLocToDest= 

	//Compute Turning Radius, CircleCenter 
	//-------------------------------------------------------------------------------------------------------------
	float turningRadius = flyingSpeed / FMath::DegreesToRadians(_yawDegreePerSecond);
	FVector dirRight = GetActionOwner()->GetActorRightVector();
	dirRight.Z = 0;
	dirRight.Normalize();
	FVector circleCenter = angle_Forward_ToDest < 0
		? GetActionOwner()->GetActorLocation() - dirRight * turningRadius
		: GetActionOwner()->GetActorLocation() + dirRight * turningRadius;

	//float distanceFronCurLocToDest = UMyBlueprintFunctionLibrary::ComputeDistance(_actionOwner->GetActorLocation(), _destination, EPlane::Plane_XY);
	float distanceFronDestLocToCircleCenter = UMyBlueprintFunctionLibrary::ComputeDistance(_destination, circleCenter, EPlane::Plane_XY);

	
	//debug message
	DrawDebugLine(GetWorld(), GetActionOwner()->GetActorLocation(), circleCenter, FColor::Emerald, false, -1.0f, 0U, 30.0f);
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Circle Center: " + (circleCenter).ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("Turnning Radius: ") + FString::SanitizeFloat(turningRadius));
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("DistanceToCircleCenter ") + FString::SanitizeFloat(distanceFronDestLocToCircleCenter));


	float resultDeltaYaw = deltaYaw;

	if (distanceFronDestLocToCircleCenter < turningRadius)
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

		if (deltaYaw > 0 && angle_Forward_ToDest_AfterRotation <0)
		{
			resultDeltaYaw = deltaYaw - angle_Forward_ToDest_AfterRotation;



		}

		else if (deltaYaw < 0 && angle_Forward_ToDest_AfterRotation > 0)
		{
			resultDeltaYaw =  deltaYaw - angle_Forward_ToDest_AfterRotation;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "currevtYaw: " + FString::SanitizeFloat(currentYaw));
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "DestYaw: " + FString::SanitizeFloat(destYaw));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "DeltaYaw: " + FString::SanitizeFloat(resultDeltaYaw));

	return resultDeltaYaw;
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
	float distanceTraveledDuringPitchMax =	2 * speed * (-FMath::Cos(pitchLimit) + 1) / pitchSpeed;

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

float UActionFlyTo::GetBreakingDistance_Z(float offset, float curPitch, float pitchRate)
{
	//cos(cur)- cos(cur + rate*t ) / w = distnace

	float timeToPitch0 = FMath::Abs(curPitch) / pitchRate;
	float result = FMath::Cos(FMath::DegreesToRadians(curPitch)) - cos(FMath::DegreesToRadians(curPitch + timeToPitch0 * pitchRate)) / FMath::DegreesToRadians(pitchRate);
	//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "breaking distance: " + FString::SanitizeFloat(result));
	return result;
}

