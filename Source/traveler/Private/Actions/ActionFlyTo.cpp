// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFlyTo.h"
#include "Character/CreatureCharacter.h"

UActionFlyTo::UActionFlyTo()
{
	_actionName = ActionName::FlyTo;
	_bInstantAction = false;
	_flyingSpeed = 500;

	//Roll
	_limitedRollDegree = 70.0f;
	_yawDegreePerSecond = 50;
	_rollDegreePerSecond = -30;
}

void UActionFlyTo::VExecute()
{
	Super::VExecute();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Execute Fly To"));

	if (_actionData->TryReadVectorData(ActionData::FlyToLocation, _destination))
	{
	}
	else
	{
		_state = EActionState::AS_Finished;
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

	FVector forwardVector = character->GetActorForwardVector();
	FVector upVector = character->GetActorUpVector();
	FVector rightVector = character->GetActorRightVector();

	FQuat curQuat = curTransform.GetRotation();


	//Destination Transform State
	FVector dirToDestination = curTransform.GetLocation() - _destination;
	dirToDestination.Z = 0;
	dirToDestination.Normalize();
	forwardVector.Z = 0;

	forwardVector.Normalize();

	float dot = FVector::DotProduct(forwardVector, dirToDestination);
	float angleFrontToDest = FMath::RadiansToDegrees(FMath::Acos(dot));




	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(dot));
	
	if (dot != 1.0f)
	{
		float dotR = FVector::DotProduct(rightVector, dirToDestination);

		if (dotR > 0) 
		{
			_yawDegreePerSecond = -_yawDegreePerSecond;
		}
		else
		{

		}

		//return;
	}

	//_TurnTo();



	//Yaw
	//-------------------------------------------------------------------------------------------------------------
	//FQuat yaw = FQuat(upVector, FMath::DegreesToRadians(_yawDegreePerSecond * deltaTime));
	FQuat quatYaw = FQuat(FVector::UpVector, FMath::DegreesToRadians(_yawDegreePerSecond * deltaTime));


	//Pitch
	//-------------------------------------------------------------------------------------------------------------
	FQuat quatPitch = FQuat(rightVector, FMath::DegreesToRadians(_yawDegreePerSecond * deltaTime));


	//Roll
	//-------------------------------------------------------------------------------------------------------------
	float curRollDegree = FMath::RadiansToDegrees(curQuat.GetTwistAngle(FVector::ForwardVector));
	float deltaRollDegree = _rollDegreePerSecond * deltaTime;
	
	//limit delta roll degree
	if (FMath::Abs(curRollDegree) == _limitedRollDegree) 
	{
		deltaRollDegree = 0;
	}
	else
	{
		float degreeAfterRotate = curRollDegree + deltaRollDegree;
		if (degreeAfterRotate > 0 && degreeAfterRotate > _limitedRollDegree)
		{
			deltaRollDegree = _limitedRollDegree - degreeAfterRotate;
		}

		if (deltaRollDegree < 0 && degreeAfterRotate < -_limitedRollDegree)
		{
			deltaRollDegree = -_limitedRollDegree - degreeAfterRotate;
		}
	}

	//make Roll quaternian
	FQuat quatRoll = FQuat(forwardVector, FMath::DegreesToRadians(deltaRollDegree));




	
	//apply movement
	//-------------------------------------------------------------------------------------------------------------
	FQuat combinedRotation = quatYaw * quatRoll;


	character->AddActorWorldRotation(combinedRotation);
	character->AddMovementInput(forwardVector);







	






	//FQuat res = FMath::Lerp(quatForward, quatToDest, 0.5);

	if ((curTransform.GetLocation() - _destination).IsNearlyZero(50)) 
	{
		_state = EActionState::AS_Finished;
		return;
	}

	

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("CurrentRoll: ") + FString::SanitizeFloat(curRollDegree));
	//_preRoll = curRollDegree;

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,TEXT("CurrentRoll: ") + FString::SanitizeFloat(curRollDegree));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,TEXT("DeltaRoll: ") + FString::SanitizeFloat(deltaRollDegree));

	//_actionOwner->SetActorRotation(quatToDest);
	

	//_state = EActionState::AS_Finished;
}

