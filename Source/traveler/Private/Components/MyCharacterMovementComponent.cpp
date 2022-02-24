// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Interface/AttributeInterface.h"
#include "Interface/ActionInterface.h"
#include "Interface/AnimationModelProvider.h"


UMyCharacterMovementComponent::UMyCharacterMovementComponent()
{
	_rollLimit = 60.0f;
	_rollRate = 10.0f;

	_pitchLimit = 60.0f;
	_pitchRate = 10.0f;

	_yawRate = 10.0f;
}

void UMyCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	_actionInterface = GetOwner<IActionInterface>();
	_attributeInterface = GetOwner<IAttributeInterface>();
	_animationModelProviderInterface = GetOwner<IAnimationModelProvider>();
	

	if(_attributeInterface && _actionInterface)
	{
		//set walking speed 
		UCharacterAttribute* WalkingSpeed = _attributeInterface->VGetAttribute(EAttributeType::EATT_WalkingSpeed);
		if (WalkingSpeed)
		{
			MaxWalkSpeed = WalkingSpeed->GetValue();
		}

		_actionInterface->VGetActionBlackBoard()->
			GetValueChangedDelegate_Bool(EActionDataKey::EACTD_WantToSprint).AddUFunction(this, FName(TEXT("OnCharacterWantToSprint")));
	}
}

void UMyCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_animationModelProviderInterface)
	{
		FAnimationModel& model = _animationModelProviderInterface->VGetAnimationModelRef();
		model.MovingVelocity = Velocity;
		model.MovementMode = MovementMode;

		FVector horizonVelocity = Velocity;
		horizonVelocity.Z = 0;

		float speed = horizonVelocity.Size();
		model.bIsSprinting = speed > model.WalkingSpeed+0.1f;
		model.NormalizedSpeed = speed / model.SprintSpeed;
		model.NormalizedSpeed_IdleWalk = speed / model.WalkingSpeed;
		model.NormalizedSpeed_WalkSprint = (speed - model.WalkingSpeed) / (model.SprintSpeed - model.WalkingSpeed);
		model.PendingInput = GetPendingInputVector();
	}
}

void UMyCharacterMovementComponent::OnCharacterWantToSprint(bool wantToSprint)
{
	if (_attributeInterface)
	{
		if (wantToSprint)
		{
			//set to Sprint speed 
			UCharacterAttribute* speed = _attributeInterface->VGetAttribute(EAttributeType::EATT_SprintSpeed);
			if (speed)
			{
				MaxWalkSpeed = speed->GetValue();
			}
		}
		else
		{
			//set to walking speed 
			UCharacterAttribute* speed = _attributeInterface->VGetAttribute(EAttributeType::EATT_WalkingSpeed);
			if (speed)
			{
				MaxWalkSpeed = speed->GetValue();
			}
		}
	}
}

void UMyCharacterMovementComponent::SimulateFlying(float deltaTime)
{
	float time = computePitchTime(10);

	

}

float UMyCharacterMovementComponent::computePitchTime(float targetAltitude)
{
	float altitudeOffset = targetAltitude - GetActorLocation().Z;


	float radPitchLimit = altitudeOffset > 0.0f ? FMath::DegreesToRadians(_pitchLimit) : FMath::DegreesToRadians(_pitchLimit) * -1;
	float radPitchRate = altitudeOffset > 0.0f ? FMath::DegreesToRadians(_pitchRate) : FMath::DegreesToRadians(_pitchRate) * -1;
	float timeToPitchLimit = _pitchLimit / _pitchRate;

	float pitchTime = 0.0f;

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
	float distanceTraveledDuringPitchMax = 2 * MaxFlySpeed * (-FMath::Cos(radPitchLimit) + 1) / radPitchRate;

	float maxSpeed = MaxFlySpeed * FMath::Sin(radPitchLimit);

	if (altitudeOffset > distanceTraveledDuringPitchMax)
	{
		pitchTime = (altitudeOffset - distanceTraveledDuringPitchMax) / timeToPitchLimit;
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

		pitchTime = FMath::Acos((2 - altitudeOffset * radPitchRate) / 2) / radPitchRate;
	}

	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "Pitch Travel: " + FString::SanitizeFloat(distanceTraveledDuringPitchMax));
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "Traveled time: " + FString::SanitizeFloat(pitchTime));
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "Altitude Offset: " + FString::SanitizeFloat(altitudeOffset));

	return pitchTime;
}
