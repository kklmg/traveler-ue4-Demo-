// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Data/ObjectData.h"
#include "Event/EventData.h"
#include "Data/AnimationModelBase.h"
#include "Actions/ActionData/ActionBlackBoard.h"

UMyCharacterMovementComponent::UMyCharacterMovementComponent()
{
	BrakingDecelerationFlying = 2000.0f;
	bWantsInitializeComponent = true;
}

void UMyCharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	_actionComp = Cast<UActionComponent>(GetOwner()->GetComponentByClass(UActionComponent::StaticClass()));
	_statusComp = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));
	_animControlComp = Cast<UAnimControlComponent>(GetOwner()->GetComponentByClass(UAnimControlComponent::StaticClass()));

	if (_eventBrokerComp)
	{
		_eventBrokerComp->RegisterEvent(NSEvent::MovementModeChanged::Name);
		_eventBrokerComp->RegisterEvent(NSEvent::VelocityChanged::Name);
		_eventData_MovementModeChanged = NewObject<UDataUInt8>(this);
		_eventData_VelocityChanged = NewObject<UDataVector>(this);

		//publish event 
		_eventData_VelocityChanged->Value = Velocity;
		_eventBrokerComp->PublishEvent(NSEvent::VelocityChanged::Name, _eventData_VelocityChanged);
		_eventData_MovementModeChanged->Value = MovementMode;
		_eventBrokerComp->PublishEvent(NSEvent::MovementModeChanged::Name, _eventData_MovementModeChanged);
	}
}

void UMyCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (_animControlComp)
	{
		_animViewModel = _animControlComp->GetAnimationModel();
		if (_animViewModel)
		{
			_animViewModel->SetUInt8(NSAnimationDataKey::byteMovementMode, MovementMode);
			_animViewModel->SetFloat(NSAnimationDataKey::fMaxSpeed, GetMaxSpeed());
			_animViewModel->SetVector(NSAnimationDataKey::vMovingVelocity, Velocity);
		}
	}

	if (_statusComp)
	{
		//set walking speed 
		MaxWalkSpeed = _statusComp->GetFinalValue(EStatusType::EStatus_WalkingSpeed);
	}

}

void UMyCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RollControl(DeltaTime);

	if (_inputDeltaPitch != 0.0f || _inputDeltaYaw != 0.0f || _inputDeltaRoll != 0.0f)
	{
		FRotator rotator = GetOwner()->GetActorRotation();
		rotator.Yaw += _inputDeltaYaw;
		rotator.Pitch += _inputDeltaPitch;
		rotator.Roll += _inputDeltaRoll;

		GetOwner()->SetActorRotation(rotator);

		_inputDeltaPitch = 0.0f;
		_inputDeltaYaw = 0.0f;
		_inputDeltaRoll = 0.0f;
	}
}

FFlyingAbilityData& UMyCharacterMovementComponent::getFlyingAbilityData()
{
	return _FlyingAbilityData;
}

FORCEINLINE_DEBUGGABLE float UMyCharacterMovementComponent::ComputeRequiredTimeToBrake()
{
	return Velocity.Size() / GetMaxBrakingDeceleration();
}

FORCEINLINE_DEBUGGABLE float UMyCharacterMovementComponent::ComputeBrakingDistance()
{
	float requiredTimeToStop = ComputeRequiredTimeToBrake();

	//s = v0t + 1/2 * at^2
	return  Velocity.Size() * requiredTimeToStop - 0.5 * GetMaxBrakingDeceleration() * requiredTimeToStop * requiredTimeToStop;
}

FORCEINLINE_DEBUGGABLE float UMyCharacterMovementComponent::ComputeDistTraveledDuringPitch0()
{
	float curPitch = GetOwner()->GetActorRotation().Pitch;
	float RequiredTimeToPitch0 = FMath::Abs(curPitch / _FlyingAbilityData.PitchAngSpeed);
	float angSpeedPitch = curPitch > 0 ? -_FlyingAbilityData.PitchAngSpeed : _FlyingAbilityData.PitchAngSpeed;

	//Desc:
	//v = sin(curPitch + pitchAngSpeed * deltaTime) * velocity_Z
	//Integral => - cos(curPitch + pitchAngSpeed * deltaTime) / pitchAngSpeed * velcocityZ
	//shift = (VelocityZ* (-cos(curPitch + pitchAngSpeed * RequiredTimeToPitch0) + cos(curPitch))) / pitchAngSpeed

	float shift = Velocity.Z *
		(-FMath::Cos(FMath::DegreesToRadians(curPitch + angSpeedPitch * RequiredTimeToPitch0)) + FMath::Cos(FMath::DegreesToRadians(curPitch))) / FMath::DegreesToRadians(angSpeedPitch);

	return shift;
}

void UMyCharacterMovementComponent::Accelerate(bool bPositive, float deltaTime)
{
	//AddInputVector(bPositive ? GetOwner()->GetActorForwardVector() : -GetOwner()->GetActorForwardVector());

	if (bPositive)
	{
		AddInputVector(GetOwner()->GetActorForwardVector());
	}
	else
	{
		StopActiveMovement();
	}
}

void UMyCharacterMovementComponent::RotateYaw(bool bPositive, float deltaTime, float scale)
{
	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		_inputDeltaYaw = bPositive ? _FlyingAbilityData.YawAngSpeed * deltaTime * scale :
			-_FlyingAbilityData.YawAngSpeed * deltaTime * scale;


	}
	//todo
	else
	{
	}
}

void UMyCharacterMovementComponent::RotateToYaw(float destYaw, float deltaTime)
{
	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		float deltaYaw = _FlyingAbilityData.YawAngSpeed * deltaTime;
		deltaYaw = destYaw > 0 ?
			FMath::Min(deltaYaw, destYaw) : FMath::Max(-deltaYaw, destYaw);

		_inputDeltaYaw = deltaYaw;
	}
	//todo
	else
	{
	}
}

void UMyCharacterMovementComponent::Ascend(bool bPositive, float deltaTime)
{
	check(GetOwner())
		FRotator curRotator = GetOwner()->GetActorRotation();

	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		float deltaPitch = _FlyingAbilityData.PitchAngSpeed * deltaTime;

		deltaPitch = bPositive ?
			FMath::Min(deltaPitch, _FlyingAbilityData.PitchLimit - curRotator.Pitch) :
			FMath::Max(-deltaPitch, -_FlyingAbilityData.PitchLimit - curRotator.Pitch);

		_inputDeltaPitch += deltaPitch;
	}


	if (bPositive)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Ascend: ");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "descend: ");
	}
}

void UMyCharacterMovementComponent::KeepHorizontal(float deltaTime)
{
	check(GetOwner())
		FRotator curRotator = GetOwner()->GetActorRotation();

	if (curRotator.Pitch == 0.0f)
	{
		return;
	}

	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		float deltaPitch = _FlyingAbilityData.PitchAngSpeed * deltaTime;

		_inputDeltaPitch = curRotator.Pitch > 0 ?
			FMath::Max(-deltaPitch, 0.0f - curRotator.Pitch) :
			FMath::Min(deltaPitch, 0.0f - curRotator.Pitch);
		_inputDeltaPitch += deltaPitch;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Keep Horizontal: ");
}

void UMyCharacterMovementComponent::KeepSpeed(float normalizedSpeed, float deltaTime)
{
	float speed = FMath::Lerp(0.0f, GetMaxSpeed(), normalizedSpeed);

	if (Velocity.Size() > speed)
	{
		Accelerate(false, deltaTime);
	}
	else
	{
		Accelerate(true, deltaTime);
	}
}

void UMyCharacterMovementComponent::ToggleSprint(bool bSprint)
{
	if (_bToggleSprint == bSprint) return;
	if (_statusComp == nullptr) return;
	_bToggleSprint = bSprint;
	MaxWalkSpeed = _statusComp->GetFinalValue(_bToggleSprint ? EStatusType::EStatus_SprintingSpeed : EStatusType::EStatus_WalkingSpeed);
}

void UMyCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if (_animViewModel)
	{
		_animViewModel->SetUInt8(NSAnimationDataKey::byteMovementMode, MovementMode);
		_animViewModel->SetFloat(NSAnimationDataKey::fMaxSpeed, GetMaxSpeed());
	}

	if (_eventBrokerComp)
	{
		_eventData_MovementModeChanged->Value = MovementMode;
		_eventBrokerComp->PublishEvent(NSEvent::MovementModeChanged::Name, _eventData_MovementModeChanged);
	}
}

void UMyCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (_animViewModel)
	{
		_animViewModel->SetVector(NSAnimationDataKey::vMovingVelocity, Velocity);
	}

	if (_eventBrokerComp)
	{
		_eventData_VelocityChanged->Value = Velocity;
		_eventBrokerComp->PublishEvent(NSEvent::VelocityChanged::Name, _eventData_VelocityChanged);
	}
}

void UMyCharacterMovementComponent::RollControl(float deltaTime)
{
	float curRoll = GetOwner()->GetActorRotation().Roll;

	if (_inputDeltaYaw > 0)
	{
		_inputDeltaRoll = FMath::Min(_inputDeltaYaw, _FlyingAbilityData.RollLimit - curRoll);
	}
	else if (_inputDeltaYaw < 0)
	{
		_inputDeltaRoll = FMath::Max(-_inputDeltaYaw, -_FlyingAbilityData.RollLimit - curRoll);
	}
	else if (curRoll != 0)
	{
		_inputDeltaRoll = curRoll > 0 ? FMath::Max(-_FlyingAbilityData.RollAngSpeed * deltaTime, 0 - curRoll) 
		: FMath::Min(_FlyingAbilityData.RollAngSpeed * deltaTime, curRoll - 0);
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("_inputDeltaRoll : %f"), _inputDeltaRoll));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("_inputDeltaYaw : %f"), _inputDeltaYaw));
}
