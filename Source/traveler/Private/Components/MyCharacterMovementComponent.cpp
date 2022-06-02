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
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UMyCharacterMovementComponent::UMyCharacterMovementComponent()
{
	BrakingDecelerationFlying = 2000.0f;
	_timeDilation = 1.0f;
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
		_eventBrokerComp->RegisterEvent(NSEventData::MovementModeChanged::Name);
		_eventBrokerComp->RegisterEvent(NSEventData::VelocityChanged::Name);
		_eventData_MovementModeChanged = NewObject<UDataUInt8>(this);
		_eventData_VelocityChanged = NewObject<UDataVector>(this);

		//publish event 
		_eventData_VelocityChanged->Value = Velocity;
		_eventBrokerComp->PublishEvent(NSEventData::VelocityChanged::Name, _eventData_VelocityChanged);
		_eventData_MovementModeChanged->Value = MovementMode;
		_eventBrokerComp->PublishEvent(NSEventData::MovementModeChanged::Name, _eventData_MovementModeChanged);
	}
}

void UMyCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (_animControlComp)
	{
		_animViewModel = _animControlComp->GetAnimViewModel();
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
		MaxFlySpeed = _statusComp->GetFinalValue(EStatusType::EStatus_FlyingSpeed);
	}

	if (_eventBrokerComp)
	{
		_eventBrokerComp->SubscribeEvent<UMyCharacterMovementComponent>
			(NSEventData::ActorLifeStateChanged::Name, this, &UMyCharacterMovementComponent::OnReceiveEvent_ActorLifeStateChanged);
	}

}

void UMyCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	DeltaTime = _timeDilation * DeltaTime;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_inputDeltaPitch != 0.0f || _inputDeltaYaw != 0.0f)
	{
		FRotator rotator = GetOwner()->GetActorRotation();
		rotator.Yaw += _inputDeltaYaw;
		rotator.Pitch += _inputDeltaPitch;
		rotator.Roll = FMath::Lerp(-60, 60, (_curYawSpeed + _FlyingAbilityData.YawAngSpeedMax) / (_FlyingAbilityData.YawAngSpeedMax * 2));

		GetOwner()->SetActorRotation(rotator);
		Velocity = rotator.Vector().GetSafeNormal() * Velocity.Size();

		_inputDeltaPitch = 0.0f;
		_inputDeltaYaw = 0.0f;
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
		_curYawSpeed = bPositive ?
			FMath::Min(_curYawSpeed + _FlyingAbilityData.YawAcc * deltaTime * scale, _FlyingAbilityData.YawAngSpeedMax) :
			FMath::Max(_curYawSpeed - _FlyingAbilityData.YawAcc * deltaTime * scale, -_FlyingAbilityData.YawAngSpeedMax);

		_inputDeltaYaw = _curYawSpeed * deltaTime;

		if (bPositive)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("turn right"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("turn left"));
		}
	}
	//todo
	else
	{
	}
}

void UMyCharacterMovementComponent::KeepYawSpeed(float desiredYawSpeed, float deltaTime)
{
	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("curYawSpeed : %f"), _curYawSpeed));
		desiredYawSpeed = desiredYawSpeed > 0 ?
			FMath::Min(desiredYawSpeed, _FlyingAbilityData.YawAngSpeedMax) : FMath::Max(desiredYawSpeed, -_FlyingAbilityData.YawAngSpeedMax);

		if (desiredYawSpeed > _curYawSpeed)
		{
			_curYawSpeed = FMath::Min(_curYawSpeed + _FlyingAbilityData.YawAcc * deltaTime, desiredYawSpeed);
		}
		else
		{
			_curYawSpeed = FMath::Max(_curYawSpeed - _FlyingAbilityData.YawAcc * deltaTime, -desiredYawSpeed);
		}

		_inputDeltaYaw = _curYawSpeed * deltaTime;
	}
	//todo
	else
	{
	}
}

void UMyCharacterMovementComponent::RotateDeltaYaw(float deltaYawAng, float deltaTime)
{
	if (deltaYawAng == 0.0f) return;

	if (MovementMode == EMovementMode::MOVE_Flying)
	{
		float acceleratedYawSpeed = FMath::Min(_curYawSpeed + _FlyingAbilityData.YawAcc * deltaTime, _FlyingAbilityData.YawAngSpeedMax);
		float deceleratedYawSpeed = FMath::Max(_curYawSpeed - _FlyingAbilityData.YawAcc * deltaTime, -_FlyingAbilityData.YawAngSpeedMax);

		//-------------------------------------------------------
		//v0: Desired Angular Speed(Initial Angular Speed) 
		//s: Braking Shift,
		//t: Braking Time,
		//acc: angular acceleration
		// 
		//s = v0 * t - 0.5 * acc * t * t, t = v0 / a 
		//=> s = v0 * v0 = 2 * acc
		//=> v0 = sqrt(s * acc * 2)
		//---------------------------------------------------------
		float desiredYawSpeed = deltaYawAng > 0 ?
			FMath::Sqrt(deltaYawAng * _FlyingAbilityData.YawAcc * 2) : -FMath::Sqrt(deltaYawAng * -_FlyingAbilityData.YawAcc * 2);

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("curYawSpeed : %f"), _curYawSpeed));
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("desiredYawSpeed : %f"), desiredYawSpeed));


		{
			if (_curYawSpeed < desiredYawSpeed)
			{
				if (acceleratedYawSpeed > desiredYawSpeed)
				{
					_curYawSpeed = desiredYawSpeed;
					_inputDeltaYaw = (desiredYawSpeed) * deltaTime;
				}
				else
				{
					_curYawSpeed = acceleratedYawSpeed;
					_inputDeltaYaw = acceleratedYawSpeed * deltaTime;

				}
			}
			else
			{
				if (deceleratedYawSpeed < desiredYawSpeed)
				{
					_curYawSpeed = desiredYawSpeed;
					_inputDeltaYaw = (desiredYawSpeed)*deltaTime;
				}
				else
				{
					_curYawSpeed = deceleratedYawSpeed;
					_inputDeltaYaw = deceleratedYawSpeed * deltaTime;
				}
			}
		}

	/*	if (deltaYawAng > 0 && _inputDeltaYaw > deltaYawAng)
		{
			_inputDeltaYaw = deltaYawAng;
			_curYawSpeed = 0;
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("000000000000000000000000000000")));
		}
		if (deltaYawAng < 0 && _inputDeltaYaw < deltaYawAng)
		{
			_inputDeltaYaw = deltaYawAng;
			_curYawSpeed = 0;
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("0000000000000000000000000000000")));
		}*/


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

		deltaPitch = curRotator.Pitch > 0 ?
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
	MaxFlySpeed = _statusComp->GetFinalValue(EStatusType::EStatus_FlyingSpeed) * (_bToggleSprint ? 4.0f : 1.0f);
}

float UMyCharacterMovementComponent::GetCurrentYawSpeed()
{
	return _curYawSpeed;
}

void UMyCharacterMovementComponent::SetTimeDilation(float timeDilation)
{
	_timeDilation = timeDilation;
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
		_eventBrokerComp->PublishEvent(NSEventData::MovementModeChanged::Name, _eventData_MovementModeChanged);
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
		_eventBrokerComp->PublishEvent(NSEventData::VelocityChanged::Name, _eventData_VelocityChanged);
	}

}

void UMyCharacterMovementComponent::OnReceiveEvent_ActorLifeStateChanged(UObject* baseData)
{
	auto eventData = Cast<NSEventData::ActorLifeStateChanged::Type>(baseData);
	if (eventData)
	{
		if (eventData->Value == false)
		{
			if (MovementMode == EMovementMode::MOVE_Flying)
			{
				//GetCharacterOwner()->GetCapsuleComponent()->SetSimulatePhysics(true);
				SetMovementMode(EMovementMode::MOVE_Falling);
			}
		}
		else
		{
			//GetCharacterOwner()->GetCapsuleComponent()->SetSimulatePhysics(false);
			//GetCharacterOwner()->GetMesh()->SetSimulatePhysics(false);
		}
	}
}
