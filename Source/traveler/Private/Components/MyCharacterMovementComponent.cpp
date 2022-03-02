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

void UMyCharacterMovementComponent::StartSimulationFlyingUp(float targetAltitude)
{
	_simulationData = GenerateFlyingUpSimulationData(targetAltitude);
	_simulationData.bIsSimulating = true;
}

void UMyCharacterMovementComponent::SimulationTick(float deltaTime)
{
	if (_simulationData.bIsSimulating)
	{
		_simulationData.ElapsedTime += deltaTime;
	}
}

FFlygingSimulationData UMyCharacterMovementComponent::GenerateFlyingUpSimulationData(float targetAltitude)
{

	float altitudeOffset = FMath::Abs(targetAltitude - GetActorLocation().Z);
	float radPitchLimit = FMath::DegreesToRadians(_pitchLimit);
	float radPitchRate = FMath::DegreesToRadians(_pitchRate);
	float durationAcclerateToMax = _pitchLimit / _pitchRate;

	float duration_Accelerate = 0.0f;
	float duration_Steady = 0.0f;

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
	//(-cos(wt)+1)/w * speed * 2;
	float TravelableDistanceDuringAcceleration =
					FMath::Abs(2 * MaxFlySpeed * (1 - FMath::Cos(radPitchLimit)) / radPitchRate);

	float maxSpeed = MaxFlySpeed * FMath::Sin(radPitchLimit);

	if (altitudeOffset > TravelableDistanceDuringAcceleration)
	{
		duration_Accelerate = _pitchLimit / _pitchRate;
		duration_Steady = (altitudeOffset - TravelableDistanceDuringAcceleration) / maxSpeed;
	}
	else
	{
		//speed * (1 - cos(wt)) / w = altitudeOffset / 2
		//=>time_acc = arccos(1 - (altitudeOffset * w / (2 * speed) ) ) / w
		duration_Accelerate = FMath::Acos((1 - ((altitudeOffset * radPitchRate) / (2 * MaxFlySpeed)))) / radPitchRate;
		duration_Steady = 0;
	}


	FFlygingSimulationData simulationData;
	simulationData.TimeFrame_StartAccelerate = 0;
	simulationData.TimeFrame_OnMaxSpeed = simulationData.TimeFrame_StartAccelerate + duration_Accelerate;
	simulationData.TimeFrame_StartDecelerate = simulationData.TimeFrame_OnMaxSpeed + duration_Steady;
	simulationData.TimeFrame_Stop = simulationData.TimeFrame_StartDecelerate + duration_Accelerate;


//	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "Travelable Distance during Acceleration: " + FString::SanitizeFloat(TravelableDistanceDuringAcceleration));
//	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "Altitude Offset: " + FString::SanitizeFloat(altitudeOffset));
//	simulationData.ShowDebugMessage();

	return simulationData;
}
