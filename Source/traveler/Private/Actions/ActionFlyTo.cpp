// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameSystem/MyBlueprintFunctionLibrary.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actions/ActionData/ActionData_FVector.h"


UActionFlyTo::UActionFlyTo()
{
	_actionName = ActionName::FlyTo;
	_actionType = EActionType::EACT_FlyTo;

	_bInstantAction = false;
	_flyingSpeed = 2000;
	_turnningSpeed = 500;

	//Roll
	_limitedRollDegree = 80.0f;
	_limitedPitchDegree = 80.0f;
	_yawDegreePerSecond = 25;
	_pitchDegreePerSecond = 10;
	_rollDegreePerSecond = -30;
	_resetFactor = 0;
	_resetFactorSpeed = 0.5f;
}

void UActionFlyTo::VExecute()
{
	Super::VExecute();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

	if (_actionBlackBoard->TryGetData_FVector(EActionData::EACTD_DestLocation,_destination))
	{
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
	FRotator curRotator = curQuat.Rotator();

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
	DrawDebugLine(GetWorld(), _actionOwner->GetActorLocation(), _actionOwner->GetActorLocation() + forwardVector * 750, FColor::Blue, false, -1.0f, 0U, 30.0f);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(distance));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Velocity: " + FString::SanitizeFloat((character->GetVelocity()).Size()));



	//Check Is at destination
	//-------------------------------------------------------------------------------------------------------------
	if (distance < 1000)
	{
		if(_resetFactor==1.0f)
		{
			_state = EActionState::AS_SUCCEEDED;
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


	FRotator newRotation = forwardVector.Rotation();
	FVector newForwardVector = forwardVector;


	//Yaw
	//-------------------------------------------------------------------------------------------------------------
	float deltaYaw = _YawTurnning(dirToDestination, forwardVector, deltaTime);
	newRotation.Yaw += deltaYaw;


	//Pitch
	//-------------------------------------------------------------------------------------------------------------
	float curPitch = forwardVector.Rotation().Pitch;

	//float verticalSpeed = _flyingSpeed * FMath::Sin(curPitch);
	//float HorizontalSpeed = _flyingSpeed * FMath::Cos(curPitch);

	//float s = curPitch / _pitchDegreePerSecond;
	//float d = verticalSpeed

	float heightOffset = _destination.Z - curLocation.Z;

	//if(heightOffset)


	float deltaPitch = _pitchDegreePerSecond * deltaTime;


	float pitchAfterRotation = 0;
	if (FMath::Abs(heightOffset) < 100)
	{
		if (curPitch == 0)
		{
			deltaPitch = 0;
		}
		else
		{
			deltaPitch = -curPitch;
		}
	}
	else
	{
		if (heightOffset < 0)
		{
			deltaPitch = -deltaPitch;
		}
		pitchAfterRotation = curPitch + deltaPitch;
		pitchAfterRotation = FMath::Clamp(pitchAfterRotation, -_limitedPitchDegree, _limitedPitchDegree);

		deltaPitch = pitchAfterRotation - curPitch;
	}


	newRotation.Pitch += deltaPitch;
	newForwardVector = newRotation.Vector();


	FQuat turnQuat = FQuat::FindBetween(forwardVector,newForwardVector);

	//apply movement
	//-------------------------------------------------------------------------------------------------------------
	character->AddActorWorldRotation(turnQuat);
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

