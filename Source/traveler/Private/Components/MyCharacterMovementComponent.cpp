// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Data/ObjectData.h"
#include "Event/EventNames.h"
#include "Data/AnimationModelBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"

UMyCharacterMovementComponent::UMyCharacterMovementComponent()
{
}

FFlyingAbilityData& UMyCharacterMovementComponent::getFlyingAbilityData()
{
	return _FlyingAbilityData;
}

float UMyCharacterMovementComponent::ComputeRequiredTimeToStopXY()
{
	float curSpeedXY = Velocity.Size2D();
	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		return curSpeedXY / _FlyingAbilityData.AccelXY;
	}

	//todo 
	return 0.0f;
}

float UMyCharacterMovementComponent::ComputeDistTraveledDuringDecelerateTo0()
{
	float curSpeedXY = Velocity.Size2D();
	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		float requiredTimeToStopXY = curSpeedXY / _FlyingAbilityData.AccelXY;

		//s = v0t + 1/2 * at^2
		return  curSpeedXY * requiredTimeToStopXY - _FlyingAbilityData.AccelXY * requiredTimeToStopXY * requiredTimeToStopXY * 0.5;
	}

	//todo 
	return 0.0f;
}

void UMyCharacterMovementComponent::AccelerateXY(bool bPositive, float deltaTime)
{
	check(GetOwner())

	//forward planeXY
	FVector actorForwardXY = GetOwner()->GetActorForwardVector();
	actorForwardXY.Z = 0;
	actorForwardXY.Normalize();

	float curSpeedXY = Velocity.Size2D();

	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		AddInputVector(bPositive ? actorForwardXY  : -actorForwardXY );
	}
	//todo
	else
	{
	}
}

void UMyCharacterMovementComponent::Accelerate(bool bPositive, float deltaTime)
{
	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		AddInputVector(bPositive ? GetOwner()->GetActorForwardVector() : -GetOwner()->GetActorForwardVector());
	}
	//todo
	else
	{
	}
}

void UMyCharacterMovementComponent::AccelerateZ(bool bPositive, float deltaTime)
{
	check(GetOwner())





	//	if (MovementMode == EMovementMode::MOVE_Flying)
	//	{
	//		float deltaSpeedZ = bPositive ?
	//			FMath::Min(_FlyingAbilityData.AccelZ * deltaTime, _FlyingAbilityData.SpeedZMax - Velocity.Z) :
	//			FMath::Max(-_FlyingAbilityData.AccelZ * deltaTime, -_FlyingAbilityData.SpeedZMax - Velocity.Z);

	//		Velocity.Z += deltaSpeedZ;
	//	}
	////todo
	//	else
	//	{

	//	}
}

void UMyCharacterMovementComponent::KeepSpeedXY(float normalizedSpeed, float deltaTime)
{
	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		float speedXY = FMath::Lerp(0.0f, _FlyingAbilityData.SpeedXYMax, normalizedSpeed);
		float curSpeedXY = Velocity.Size2D();

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "speedXY: " + FString::SanitizeFloat(speedXY));
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "curSpeedXY: " + FString::SanitizeFloat(curSpeedXY));

		if (curSpeedXY > speedXY) 
		{
			AccelerateXY(false, deltaTime);
		}
		else
		{
			AccelerateXY(true, deltaTime);
		}
	}
}

void UMyCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	_actionComp = Cast<UActionComponent>(GetOwner()->GetComponentByClass(UActionComponent::StaticClass()));
	_statusComp = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));

	if (_statusComp && _actionComp)
	{
		//set walking speed 
		MaxWalkSpeed = _statusComp->GetFinalValue(EStatusType::EStatus_WalkingSpeed);

		_actionComp->GetActionBlackBoard()->
			GetValueChangedDelegate_Bool(EActionDataKey::EACTD_WantToSprint).AddUObject(this, &UMyCharacterMovementComponent::OnCharacterWantToSprint);
	}

	UAnimControlComponent* animControlComp = Cast<UAnimControlComponent>(GetOwner()->GetComponentByClass(UAnimControlComponent::StaticClass()));
	if (animControlComp)
	{
		_animationViewModel = animControlComp->GetAnimationModel();
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

	if (_animationViewModel)
	{
		_animationViewModel->SetUInt8(NSAnimationDataKey::byteMovementMode, MovementMode);
	}
	PublishMovementModeChangedEvent();
}

void UMyCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (_animationViewModel)
	{
		_animationViewModel->SetVector(NSAnimationDataKey::vMovingVelocity, Velocity);
	}
}

void UMyCharacterMovementComponent::PublishMovementModeChangedEvent()
{
	if (_eventBrokerComp)
	{
		UDataInt32* eventData = NewObject<UDataInt32>(this);
		eventData->Value = MovementMode;
		_eventBrokerComp->PublishEvent(NSEventNames::MovementModeChanged, eventData);
	}
}

void UMyCharacterMovementComponent::OnCharacterWantToSprint(bool wantToSprint)
{
	if (_statusComp)
	{
		if (wantToSprint)
		{
			MaxWalkSpeed = _statusComp->GetFinalValue(EStatusType::EStatus_SprintingSpeed);
		}
		else
		{

			MaxWalkSpeed = _statusComp->GetFinalValue(EStatusType::EStatus_WalkingSpeed);
		}
	}
}
