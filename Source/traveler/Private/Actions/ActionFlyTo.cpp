// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"


UActionFlyTo::UActionFlyTo()
{
	_actionName = ActionName::FlyTo;
	_bInstantAction = false;
	_flyingSpeed = 2000;
	_turnningSpeed = 500;

	//Roll
	_limitedRollDegree = 70.0f;
	_yawDegreePerSecond = 60;
	_rollDegreePerSecond = -30;
}

void UActionFlyTo::VExecute()
{
	Super::VExecute();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

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
	FTransform curTransform = character->GetActorTransform();
	FVector curLocation = curTransform.GetLocation();

	FVector forwardVector = character->GetActorForwardVector();
	FVector upVector = character->GetActorUpVector();
	FVector rightVector = character->GetActorRightVector();



	FQuat curQuat = curTransform.GetRotation();


	//Destination Transform State
	FVector dirToDestination = _destination - curLocation;
	//dirToDestination.Z = 0;
	//dirToDestination.Normalize();
	//forwardVector.Z = 0;

	//forwardVector.Normalize();

	//float dot = FVector::DotProduct(forwardVector, dirToDestination);
	//float angleFrontToDest = FMath::RadiansToDegrees(FMath::Acos(dot));

	FVector destLocXY(_destination.X, _destination.Y, curLocation.Z);

	float distance = (_destination - curLocation).Size();

	
	DrawDebugLine(GetWorld(), curLocation, _destination, FColor::Red, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), curLocation, destLocXY, FColor::Green, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), curLocation, curLocation+forwardVector*1000, FColor::Blue, false, -1.0f, 0U, 100.0f);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Current Location: " + (curLocation).ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Dest Location: " + (destLocXY).ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat(distance));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Velocity: " + FString::SanitizeFloat((character->GetVelocity()).Size()));
	if (distance < character->GetSimpleCollisionRadius()+1000)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "fly to completed ");
		_state = EActionState::AS_SUCCEEDED;
		return;
	}

	DrawDebugPoint(GetWorld(), curLocation, 1, FColor::Black, true, 10.0f, 50.0f);


	float r = _flyingSpeed / FMath::DegreesToRadians(_yawDegreePerSecond);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "RRRRR: " + FString::SanitizeFloat(r));

	DrawDebugLine(GetWorld(), curLocation - rightVector * r, curLocation, FColor::Purple, false, -1.0f, 0, 30.f);
	DrawDebugLine(GetWorld(), curLocation + rightVector * r, curLocation, FColor::Purple, false, -1.0f, 0, 30.f);



	FQuat deltaQuat = FQuat::Identity;
	
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


	deltaQuat = quatYaw /** quatRoll*/;
	

	//apply movement
	//-------------------------------------------------------------------------------------------------------------
	character->AddActorWorldRotation(deltaQuat);
	character->AddMovementInput(forwardVector);



	//FQuat res = FMath::Lerp(quatForward, quatToDest, 0.5);


	

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("CurrentRoll: ") + FString::SanitizeFloat(curRollDegree));
	//_preRoll = curRollDegree;

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,TEXT("CurrentRoll: ") + FString::SanitizeFloat(curRollDegree));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,TEXT("DeltaRoll: ") + FString::SanitizeFloat(deltaRollDegree));

	//_actionOwner->SetActorRotation(quatToDest);
	

	//_state = EActionState::AS_Finished;
}


float UActionFlyTo::_YawTurnning(FVector dirToDestination, FVector dirForward, float deltaTime)
{
	//Direction to Destination
	dirToDestination.Z = 0;
	dirToDestination.Normalize();

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, "Direction To Destination on xyPlane: " + dirToDestination.ToString());

	//Direction Forward
	dirForward.Z = 0;
	dirForward.Normalize();

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, "Direction Forward xyPlane: " + dirForward.ToString());


	//compute delta Degree 
	float currentYaw = dirForward.Rotation().Yaw;
	float destYaw = dirToDestination.Rotation().Yaw;
	float angleBetween_Forward_ToDest = FMath::FindDeltaAngleDegrees(destYaw, currentYaw);
	float deltaYaw = angleBetween_Forward_ToDest < 0 ? _yawDegreePerSecond * deltaTime : -_yawDegreePerSecond * deltaTime;

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "angleBetween_Front_ToDest: " + FString::SanitizeFloat(angleBetween_Forward_ToDest));


	if (FMath::Abs(angleBetween_Forward_ToDest) == 0)
	{
		deltaYaw = 0;
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, "turned to completed ");
	}
	else
	{
		float yawAfterRotation = currentYaw + deltaYaw;

	

		//if (deltaYaw > 0 && yawAfterRotation > destYaw)
		//{
		//	deltaYaw = yawAfterRotation - destYaw;
		//}

		//if (deltaYaw < 0 && yawAfterRotation < destYaw)
		//{
		//	deltaYaw = yawAfterRotation - destYaw;
		//}
	}

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
