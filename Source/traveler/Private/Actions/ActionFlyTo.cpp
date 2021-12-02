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
	_yawDegreePerSecond = 30;
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

	
	DrawDebugLine(GetWorld(), curLocation, _destination, FColor::Red, false, -1.0f, 0U, 30.0f);
	DrawDebugLine(GetWorld(), curLocation, destLocXY, FColor::Green, false, -1.0f, 0U, 30.0f);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Current Location: " + (curLocation).ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Dest Location: " + (destLocXY).ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Distance: " + FString::SanitizeFloat((_destination - curLocation).Size()));

	if ((destLocXY - curLocation).Size()<100)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "fly to completed ");
		_state = EActionState::AS_Finished;
		return;
	}


	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(dot));
	//
	//if (dot == 1.0f)
	//{
	//	_yawDegreePerSecond = 0;

	//	_state = EActionState::AS_Finished;
	//	return;
	//}
	//else
	//{
	//	float dotR = FVector::DotProduct(rightVector, dirToDestination);

	//	if (dotR > 0)
	//	{
	//		_yawDegreePerSecond = -_yawDegreePerSecond;
	//		_rollDegreePerSecond = -_rollDegreePerSecond;
	//	}
	//	else
	//	{

	//	}
	//}

	//_TurnTo();



	//Yaw
	//-------------------------------------------------------------------------------------------------------------
	//FQuat yaw = FQuat(upVector, FMath::DegreesToRadians(_yawDegreePerSecond * deltaTime));
	//float curYawDegree = FMath::RadiansToDegrees(curQuat.GetTwistAngle(FVector::UpVector));
	//float curYawDegree = curQuat.Rotator().Yaw;
	float deltaYawDegree = _yawDegreePerSecond * deltaTime;

	//to Dest
	FVector dirToDest_XYPlane = dirToDestination;
	dirToDest_XYPlane.Z = 0;
	dirToDest_XYPlane.Normalize();
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, "To Dest xyPlane: " + dirToDest_XYPlane.ToString());

	//Forward
	FVector dirForward_XYPlane = forwardVector;
	dirForward_XYPlane.Z = 0;
	dirForward_XYPlane.Normalize();
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, "Forward xyPlane: " + dirForward_XYPlane.ToString());

	float curYawDegree = dirForward_XYPlane.Rotation().Yaw+180;

	//Right
	FVector dirRight_XYPlane = rightVector;
	dirRight_XYPlane.Z = 0;
	dirRight_XYPlane.Normalize();
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, "Right xyPlane: " + dirRight_XYPlane.ToString());



	//float yawDest = dirToDestination.Rotation().Yaw;
	float yawDest = dirToDest_XYPlane.Rotation().Yaw + 180;



	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "current Yaw: "+FString::SanitizeFloat(curYawDegree));
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Dest Yaw: " + FString::SanitizeFloat(yawDest));


	float dot = FVector::DotProduct(dirForward_XYPlane, dirToDest_XYPlane);
	float angleBetween_Forward_ToDest = FMath::RadiansToDegrees(FMath::Acos(dot));
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "angleBetween_Front_ToDest: " + FString::SanitizeFloat(angleBetween_Forward_ToDest));


	if(FMath::Abs(angleBetween_Forward_ToDest)<10)
	//if (FMath::IsNearlyEqual(curYawDegree, yawDest,5.0f))
	{
		
		deltaYawDegree = 0;
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, "turned to completed ");
	}
	else
	{
		float dotR = FVector::DotProduct(dirRight_XYPlane, dirToDest_XYPlane);
		

		if (dotR < 0)
		{
			deltaYawDegree = -deltaYawDegree;
			GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, "TurnLeft");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, "TurnRight");
		}


		float degreeAfterYawRotation = curYawDegree + deltaYawDegree;
		if (deltaYawDegree > 0 && degreeAfterYawRotation > yawDest)
		{
			deltaYawDegree = yawDest - degreeAfterYawRotation;
		}

		if (deltaYawDegree < 0 && degreeAfterYawRotation < -yawDest)
		{
			deltaYawDegree = -yawDest - degreeAfterYawRotation;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Cyan, "DeltaYawDegree: " + FString::SanitizeFloat(deltaYawDegree));















	FQuat quatYaw = FQuat(FVector::UpVector, FMath::DegreesToRadians(deltaYawDegree));

	//Pitch
	//-------------------------------------------------------------------------------------------------------------
	FQuat quatPitch = FQuat(rightVector, FMath::DegreesToRadians(_yawDegreePerSecond * deltaTime));


	//Roll
	//-------------------------------------------------------------------------------------------------------------
	//float curRollDegree = FMath::RadiansToDegrees(curQuat.GetTwistAngle(FVector::ForwardVector));
	//float deltaRollDegree = _rollDegreePerSecond * deltaTime;
	//
	////limit delta roll degree
	//if (FMath::Abs(curRollDegree) == _limitedRollDegree) 
	//{
	//	deltaRollDegree = 0;
	//}
	//else
	//{
	//	float degreeAfterRotate = curRollDegree + deltaRollDegree;
	//	if (degreeAfterRotate > 0 && degreeAfterRotate > _limitedRollDegree)
	//	{
	//		deltaRollDegree = _limitedRollDegree - degreeAfterRotate;
	//	}

	//	if (deltaRollDegree < 0 && degreeAfterRotate < -_limitedRollDegree)
	//	{
	//		deltaRollDegree = -_limitedRollDegree - degreeAfterRotate;
	//	}
	//}

	////make Roll quaternion
	//FQuat quatRoll = FQuat(forwardVector, FMath::DegreesToRadians(deltaRollDegree));




	
	//apply movement
	//-------------------------------------------------------------------------------------------------------------
	FQuat combinedRotation = quatYaw /** quatRoll*/;

	FRotator rototor;


	character->AddActorWorldRotation(combinedRotation);
	character->AddMovementInput(forwardVector);



	//FQuat res = FMath::Lerp(quatForward, quatToDest, 0.5);


	

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("CurrentRoll: ") + FString::SanitizeFloat(curRollDegree));
	//_preRoll = curRollDegree;

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,TEXT("CurrentRoll: ") + FString::SanitizeFloat(curRollDegree));
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,TEXT("DeltaRoll: ") + FString::SanitizeFloat(deltaRollDegree));

	//_actionOwner->SetActorRotation(quatToDest);
	

	//_state = EActionState::AS_Finished;
}


FQuat UActionFlyTo::_YawTurnning()
{
	return FQuat::Identity;
}

FQuat UActionFlyTo::_RollTunning() 
{
	return FQuat::Identity;
}


void UActionFlyTo::_TurnLeft()
{




}
void UActionFlyTo::_TurnRight()
{

}
