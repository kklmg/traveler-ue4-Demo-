// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameSystem/MyBlueprintFunctionLibrary.h"


UActionFlyTo::UActionFlyTo()
{
	_actionName = ActionName::FlyTo;
	_bInstantAction = false;
	_flyingSpeed = 2000;
	_turnningSpeed = 500;

	//Roll
	_limitedRollDegree = 80.0f;
	_limitedPitchDegree = 80.0f;
	_yawDegreePerSecond = 25;
	_pitchDegreePerSecond = 10;
	_rollDegreePerSecond = -30;
}

void UActionFlyTo::VExecute()
{
	Super::VExecute();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

	//_destination = _actionBlackBoard->GetValueAsVector(ActionData::FlyToLocation);

	if (_actionData->TryReadVectorData(ActionData::FlyToLocation, _destination))
	{
		_actionOwner->GetCharacterMovement()->MaxFlySpeed;
	}
	else
	{
		_state = EActionState::AS_FAILED;
	}
	
}

void UActionFlyTo::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

	check(_actionOwner != nullptr);
	ACreatureCharacter* character = Cast<ACreatureCharacter>(_actionOwner);
	check(character != nullptr);

	_flyingSpeed = character->GetCharacterMovement()->MaxFlySpeed;

	//Current Transform State
	//-------------------------------------------------------------------------------------------------------------
	FTransform curTransform = _actionOwner->GetActorTransform();
	FVector curLocation = curTransform.GetLocation();
	FQuat curQuat = curTransform.GetRotation();

	FVector forwardVector = character->GetActorForwardVector();
	FVector upVector = character->GetActorUpVector();
	FVector rightVector = character->GetActorRightVector();


	//Destination
	//-------------------------------------------------------------------------------------------------------------
	FVector dirToDestination = _destination - curLocation;
	FVector destLocXY(_destination.X, _destination.Y, curLocation.Z);
	float distance = (_destination - curLocation).Size();


	//debug message
	DrawDebugLine(GetWorld(), curLocation, _destination, FColor::Red, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), curLocation, destLocXY, FColor::Green, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), _actionOwner->GetActorLocation(), _actionOwner->GetActorLocation()+forwardVector*750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(distance));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Velocity: " + FString::SanitizeFloat((character->GetVelocity()).Size()));



	//Check Is at destination
	//-------------------------------------------------------------------------------------------------------------
	if (distance < 1000)
	{
		_state = EActionState::AS_SUCCEEDED;
		return;
	}


	//Yaw
	//-------------------------------------------------------------------------------------------------------------
	float deltaYaw = _YawTurnning(dirToDestination, forwardVector, deltaTime);
	FQuat quatYaw(FVector::UpVector, FMath::DegreesToRadians(deltaYaw));


	//Pitch
	//-------------------------------------------------------------------------------------------------------------
	float curPitch = curTransform.Rotator().Pitch;


	float heightOffset = _destination.Z - curLocation.Z;
	float deltaPitch = _pitchDegreePerSecond * deltaTime;

	if (FMath::Abs(heightOffset) < 100) 
	{
		if (curPitch == 0) 
		{
			deltaPitch = 0;
		}
		else
		{
			deltaPitch = curPitch;
		}
	}
	else
	{
		if (heightOffset > 0)
		{
			deltaPitch = -deltaPitch;
		}

		float pitchAfterRotation = curPitch + deltaPitch;

		if (deltaPitch > 0 && pitchAfterRotation > _limitedPitchDegree)
		{
			deltaPitch = _limitedPitchDegree - curPitch;
		}
		else if (deltaPitch < 0 && pitchAfterRotation < -_limitedPitchDegree)
		{
			deltaPitch = -_limitedPitchDegree - curPitch;
		}
	}

	FQuat quatPitch = FQuat(rightVector, FMath::DegreesToRadians(deltaPitch));


	//Roll
	//-------------------------------------------------------------------------------------------------------------
	FQuat quatChanged = quatPitch*quatYaw;
	FVector forwardChanged = quatChanged.RotateVector(forwardVector);

	float deltaRoll = _RollTunning(curQuat, forwardChanged, deltaYaw, deltaTime);
	FQuat quatRoll = FQuat(forwardVector, FMath::DegreesToRadians(deltaRoll));


	FQuat deltaQuat =  quatRoll * quatPitch * quatYaw;
	

	//apply movement
	//-------------------------------------------------------------------------------------------------------------
	character->AddActorWorldRotation(deltaQuat);
	character->AddMovementInput(forwardVector);
	//character->AddMovementInput(FVector::UpVector);

}


float UActionFlyTo::_YawTurnning(FVector dirToDestination, FVector dirForward, float deltaTime)
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
	float turningRadius = _flyingSpeed / FMath::DegreesToRadians(_yawDegreePerSecond);
	FVector dirRight = _actionOwner->GetActorRightVector();
	dirRight.Z = 0;
	dirRight.Normalize();
	FVector circleCenter = angle_Forward_ToDest < 0
		? _actionOwner->GetActorLocation() - dirRight * turningRadius
		: _actionOwner->GetActorLocation() + dirRight * turningRadius;

	//float distanceFronCurLocToDest = UMyBlueprintFunctionLibrary::ComputeDistance(_actionOwner->GetActorLocation(), _destination, EPlane::Plane_XY);
	float distanceFronDestLocToCircleCenter = UMyBlueprintFunctionLibrary::ComputeDistance(_destination, circleCenter, EPlane::Plane_XY);

	
	//debug message
	DrawDebugLine(GetWorld(), _actionOwner->GetActorLocation(), circleCenter, FColor::Emerald, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Circle Center: " + (circleCenter).ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("Turnning Radius: ") + FString::SanitizeFloat(turningRadius));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("DistanceToCircleCenter ") + FString::SanitizeFloat(distanceFronDestLocToCircleCenter));


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
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "afterYaw: " + FString::SanitizeFloat(angle_Forward_ToDest_AfterRotation));

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

float UActionFlyTo::_RollTunning(FQuat curQuat,FVector dirForward,float deltaYaw, float deltaTime)
{
	float curRoll = FMath::RadiansToDegrees(curQuat.GetTwistAngle(dirForward));
	float deltaRoll = _rollDegreePerSecond * deltaTime;

	/*if (deltaYaw == 0) 
	{
		if (curRoll != 0) 
		{
			deltaRoll = -curRoll;
		}
		else
		{
			deltaRoll = 0;
		}
	}
	else*/
	{
		//if (deltaYaw < 0) deltaRoll = -deltaRoll;

		//limit delta roll degree
		if (FMath::Abs(curRoll) == _limitedRollDegree)
		{
			deltaRoll = 0;
		}
		else
		{
			float rollAfterRotation = curRoll + deltaRoll;
			if (deltaRoll > 0 && rollAfterRotation > _limitedRollDegree)
			{
				deltaRoll = _limitedRollDegree - curRoll;
			}

			if (deltaRoll < 0 && rollAfterRotation < -_limitedRollDegree)
			{
				deltaRoll = -_limitedRollDegree - curRoll;
			}
		}
	}

	return deltaRoll;
}


void UActionFlyTo::_TurnLeft()
{




}
void UActionFlyTo::_TurnRight()
{

}
