// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FlyingMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UFlyingMovementComponent::UFlyingMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFlyingMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFlyingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(_bHasInput)
	{

	
	}
	
	ACreatureCharacter* character = GetOwner<ACreatureCharacter>();
	check(character != nullptr);

	//_flyingSpeed = character->GetCharacterMovement()->MaxFlySpeed;

	//Current Transform State
	//-------------------------------------------------------------------------------------------------------------
	FTransform curTransform = character->GetActorTransform();
	FVector curLocation = curTransform.GetLocation();
	FQuat curQuat = curTransform.GetRotation();

	FVector forwardVector = character->GetActorForwardVector();
	FVector upVector = character->GetActorUpVector();
	FVector rightVector = character->GetActorRightVector();


	//Destination
	//-------------------------------------------------------------------------------------------------------------
	//FVector dirToDestination = _destination - curLocation;
	//FVector destLocXY(_destination.X, _destination.Y, curLocation.Z);
	//float distance = (_destination - curLocation).Size();


	////Yaw
	////-------------------------------------------------------------------------------------------------------------
	//float deltaYaw = _YawTurnning(dirToDestination, forwardVector, deltaTime);
	//FQuat quatYaw(FVector::UpVector, FMath::DegreesToRadians(deltaYaw));


	////Pitch
	////-------------------------------------------------------------------------------------------------------------
	//float curPitch = curTransform.Rotator().Pitch;


	//float heightOffset = _destination.Z - curLocation.Z;
	//float deltaPitch = _pitchDegreePerSecond * deltaTime;

	//if (FMath::Abs(heightOffset) < 100)
	//{
	//	if (curPitch == 0)
	//	{
	//		deltaPitch = 0;
	//	}
	//	else
	//	{
	//		deltaPitch = curPitch;
	//	}
	//}
	//else
	//{
	//	if (heightOffset > 0)
	//	{
	//		deltaPitch = -deltaPitch;
	//	}

	//	float pitchAfterRotation = curPitch + deltaPitch;

	//	if (deltaPitch > 0 && pitchAfterRotation > _limitedPitchDegree)
	//	{
	//		deltaPitch = _limitedPitchDegree - curPitch;
	//	}
	//	else if (deltaPitch < 0 && pitchAfterRotation < -_limitedPitchDegree)
	//	{
	//		deltaPitch = -_limitedPitchDegree - curPitch;
	//	}
	//}

	//FQuat quatPitch = FQuat(rightVector, FMath::DegreesToRadians(deltaPitch));


	////Roll
	////-------------------------------------------------------------------------------------------------------------
	//FQuat quatChanged = quatPitch * quatYaw;
	//FVector forwardChanged = quatChanged.RotateVector(forwardVector);

	//float deltaRoll = _RollTunning(curQuat, forwardChanged, deltaYaw, deltaTime);
	//FQuat quatRoll = FQuat(forwardVector, FMath::DegreesToRadians(deltaRoll));


	//FQuat deltaQuat = quatRoll * quatPitch * quatYaw;


	////apply movement
	////-------------------------------------------------------------------------------------------------------------
	//character->AddActorWorldRotation(deltaQuat);
	//character->AddMovementInput(forwardVector);
	////character->AddMovementInput(FVector::UpVector);

}




void UFlyingMovementComponent::AddLocalPitch(float scale)
{
	_localPitchInput = _pitchRate * scale;
	_bHasInput = true;
}

void UFlyingMovementComponent::AddLocalRoll(float scale)
{
	_localPitchInput = _rollRate * scale;
	_bHasInput = true;
}

void UFlyingMovementComponent::AddWorldYaw(float scale)
{
	_worldYawInput = _yawRate * scale;
	_bHasInput = true;
}

void UFlyingMovementComponent::ClearPitchRoll()
{
//FQuat 
}

