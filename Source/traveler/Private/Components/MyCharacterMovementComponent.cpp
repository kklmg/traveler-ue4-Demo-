// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Interface/StatusInterface.h"
#include "Interface/ActionInterface.h"
#include "Interface/AnimationCommunicatorInterface.h"
#include "Interface/EventBrokerInterface.h"
#include "Event/ActorEventDataBase.h"
#include "Event/EventNames.h"

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
	_statusInterface = GetOwner<IStatusInterface>();
	_eventBrokerInterface = GetOwner<IEventBrokerInterface>();

	if(_statusInterface && _actionInterface)
	{
		//set walking speed 
		MaxWalkSpeed = _statusInterface->VGetFinalValue(EStatusType::EStatus_WalkingSpeed);

		_actionInterface->VGetActionBlackBoard()->
			GetValueChangedDelegate_Bool(EActionDataKey::EACTD_WantToSprint).AddUObject(this, &UMyCharacterMovementComponent::OnCharacterWantToSprint);
	}

	IAnimationCommunicatorInterface* animationCommunicator = GetOwner<IAnimationCommunicatorInterface>();
	if (animationCommunicator)
	{
		_animationViewModel = animationCommunicator->VGetAnimationModel();
	}

	PublishMovementModeChangedEvent();
}

void UMyCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMyCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if(_animationViewModel)
	{
		_animationViewModel->SetUInt8(AnimationDataKey::byteMovementMode, MovementMode);
	}
	PublishMovementModeChangedEvent();
}

void UMyCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (_animationViewModel)
	{
		_animationViewModel->SetVector(AnimationDataKey::vMovingVelocity, Velocity);
	}
}

void UMyCharacterMovementComponent::PublishMovementModeChangedEvent()
{
	if (_eventBrokerInterface)
	{
		UActorEventDataBase* eventData = NewObject<UActorEventDataBase>(this);
		eventData->SetActor(GetOwner());
		_eventBrokerInterface->VPublishEvent(NSEventNames::MovementModeChanged, eventData);
	}
}

void UMyCharacterMovementComponent::OnCharacterWantToSprint(bool wantToSprint)
{
	if (_statusInterface)
	{
		if (wantToSprint)
		{
			MaxWalkSpeed = _statusInterface->VGetFinalValue(EStatusType::EStatus_SprintingSpeed);
		}
		else
		{

			MaxWalkSpeed = _statusInterface->VGetFinalValue(EStatusType::EStatus_WalkingSpeed);
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
