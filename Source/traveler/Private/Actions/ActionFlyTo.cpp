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
	_limitedRollDegree = 70.0f;
	_yawDegreePerSecond = 25;
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
	FQuat quatPitch = FQuat(rightVector, FMath::DegreesToRadians(_yawDegreePerSecond * deltaTime));


	//Roll
	//-------------------------------------------------------------------------------------------------------------
	float deltaRoll = _RollTunning(curQuat, deltaYaw, deltaTime);
	FQuat quatRoll = FQuat(forwardVector, FMath::DegreesToRadians(deltaRoll));


	FQuat deltaQuat = quatYaw /** quatRoll*/;
	

	//apply movement
	//-------------------------------------------------------------------------------------------------------------
	character->AddActorWorldRotation(deltaQuat);
	character->AddMovementInput(forwardVector);


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
	float angleBetween_Forward_ToDest = FMath::FindDeltaAngleDegrees(destYaw, currentYaw);
	float deltaYaw = angleBetween_Forward_ToDest < 0 ? _yawDegreePerSecond * deltaTime : -_yawDegreePerSecond * deltaTime;

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "angleBetween_Front_ToDest: " + FString::SanitizeFloat(angleBetween_Forward_ToDest));


	
	//float distanceFromCurLocToDest= 

	//Compute Turning Radius, CircleCenter 
	//-------------------------------------------------------------------------------------------------------------
	float turningRadius = _flyingSpeed / FMath::DegreesToRadians(_yawDegreePerSecond);
	FVector circleCenter = angleBetween_Forward_ToDest < 0
		? _actionOwner->GetActorLocation() + _actionOwner->GetActorRightVector() * turningRadius
		: _actionOwner->GetActorLocation() - _actionOwner->GetActorRightVector() * turningRadius;

	//float distanceFronCurLocToDest = UMyBlueprintFunctionLibrary::ComputeDistance(_actionOwner->GetActorLocation(), _destination, EPlane::Plane_XY);
	float distanceFronDestLocToCircleCenter = UMyBlueprintFunctionLibrary::ComputeDistance(_destination, circleCenter, EPlane::Plane_XY);

	
	//debug message
	DrawDebugLine(GetWorld(), _actionOwner->GetActorLocation(), circleCenter, FColor::Emerald, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Circle Center: " + (circleCenter).ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("Turnning Radius: ") + FString::SanitizeFloat(turningRadius));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("DistanceToCircleCenter ") + FString::SanitizeFloat(distanceFronDestLocToCircleCenter));


	if (distanceFronDestLocToCircleCenter < turningRadius)
	{
		deltaYaw = 0;
	}

	else if (FMath::Abs(angleBetween_Forward_ToDest) == 0)
	{
		deltaYaw = 0;
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, "turned to completed ");
	}
	else
	{
		
	/*	float yawAfterRotation = currentYaw + deltaYaw;
		if (yawAfterRotation > 180) 
		{
			yawAfterRotation -= 180;
		}
		if (yawAfterRotation < -180) 
		{
			yawAfterRotation += 180;
		}

		if (deltaYaw > 0 && yawAfterRotation > destYaw)
		{
			deltaYaw = yawAfterRotation - destYaw;
		}

		if (deltaYaw < 0 && yawAfterRotation < destYaw)
		{
			deltaYaw = yawAfterRotation - destYaw;
		}*/
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "DeltaYaw: " + FString::SanitizeFloat(deltaYaw));

	return deltaYaw;
}

float UActionFlyTo::_RollTunning(FQuat curQuat,float deltaYaw, float deltaTime)
{
	float curRoll = FMath::RadiansToDegrees(curQuat.GetTwistAngle(FVector::ForwardVector));
	float deltaRoll = deltaYaw > 0 ? _rollDegreePerSecond * deltaTime : -_rollDegreePerSecond * deltaTime;

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
			deltaRoll = rollAfterRotation - _limitedRollDegree;
		}

		if (deltaRoll < 0 && rollAfterRotation < -_limitedRollDegree)
		{
			deltaRoll = _limitedRollDegree - rollAfterRotation;
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
