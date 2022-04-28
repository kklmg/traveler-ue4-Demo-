// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CreatureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActionComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ActorUIComponent.h"
#include "Components/PawnCameraComponent.h"
#include "Components/CameraSpringArmComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Components/IKComponent.h"
#include "Components/DamageHandlerComponent.h"
#include "Components/EffectControllerComponent.h"
#include "Components/DamageHandlerComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Components/StatusComponent.h"
#include "Components/LifeControlComponent.h"
#include "Input/InputHandlerComponent.h"
#include "Perception/AISense_Damage.h"




ACreatureCharacter::ACreatureCharacter(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	//Create Event Broker component
	if (_eventBrokerComponent == nullptr)
	{
		_eventBrokerComponent = CreateDefaultSubobject<UEventBrokerComponent>(TEXT("EventBrokerComponent"));
		check(_eventBrokerComponent != nullptr);
	}

	//life Control component
	if (_lifeControlComponent == nullptr)
	{
		_lifeControlComponent = CreateDefaultSubobject<ULifeControlComponent>(TEXT("LifeControlComponent"));
		check(_lifeControlComponent != nullptr);
	}

	//AnimControlComponent
	if (_animControlComponent == nullptr)
	{
		_animControlComponent = CreateDefaultSubobject<UAnimControlComponent>(TEXT("AnimControlComponent"));
		check(_animControlComponent);
	}

	//Create Stauts component
	if (_statusComponent == nullptr)
	{
		_statusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
		check(_statusComponent != nullptr);
	}
	
	//Create Extra Transform provider component
	if (_ExTransformProviderComp == nullptr)
	{
		_ExTransformProviderComp = CreateDefaultSubobject<UExTransformProviderComponent>(TEXT("ExTransformProviderComponent"));
		check(_ExTransformProviderComp != nullptr);
		_ExTransformProviderComp->Initialize(GetMesh());
	}

	//Create action component
	if (_actionComponent == nullptr)
	{
		_actionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
		check(_actionComponent != nullptr);
	}
	//Create Camera Spring Arm Component
	if (_cameraSpringArmComponent == nullptr)
	{
		_cameraSpringArmComponent = CreateDefaultSubobject<UCameraSpringArmComponent>(TEXT("CameraSpringArmComponent"));
		check(_cameraSpringArmComponent != nullptr);
		_cameraSpringArmComponent->SetupAttachment(GetCapsuleComponent());
	}
	// Create a first person camera component.
	if (_cameraComponent == nullptr)
	{
		_cameraComponent = CreateDefaultSubobject<UPawnCameraComponent>(TEXT("FirstPersonCamera"));
		check(_cameraComponent != nullptr);
		_cameraComponent->SetupAttachment(_cameraSpringArmComponent, USpringArmComponent::SocketName);
	}
	//Create weapon component
	if (_weaponComponent == nullptr)
	{
		_weaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
		check(_weaponComponent != nullptr);
	}
	//Create ActorUIComponent component
	if (_actorUIComponent == nullptr)
	{
		_actorUIComponent = CreateDefaultSubobject<UActorUIComponent>(TEXT("ActorUIComponent"));
		check(_actorUIComponent != nullptr);
	}

	//Create InputHandler component
	if (_inputHandlerComponent == nullptr)
	{
		_inputHandlerComponent = CreateDefaultSubobject<UInputHandlerComponent>(TEXT("InputHandlerComponent"));
		check(_inputHandlerComponent != nullptr);
	}
	
	//Damage Handler component
	if (_damageHandlerComponent == nullptr)
	{
		_damageHandlerComponent = CreateDefaultSubobject<UDamageHandlerComponent>(TEXT("DamageHandlerComponent"));
		check(_damageHandlerComponent != nullptr);
	}

	//IK
	if (_IKComponent == nullptr)
	{
		_IKComponent = CreateDefaultSubobject<UIKComponent>(TEXT("IKComponent"));
		check(_IKComponent != nullptr);
	}

	//effect controller
	if (_effectControllerComponent == nullptr)
	{
		_effectControllerComponent = CreateDefaultSubobject<UEffectControllerComponent>(TEXT("EffectControllerComponent"));
		check(_effectControllerComponent);
	}
}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACreatureCharacter::PreInitializeComponents()
{
}

// Called every frame
void ACreatureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACreatureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(_inputHandlerComponent)
	{
		_inputHandlerComponent->BindInputs(PlayerInputComponent);
	}
	if (_weaponComponent)
	{
		_weaponComponent->BindInputs(PlayerInputComponent);
	}

}

float ACreatureCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
}

void ACreatureCharacter::VCameraArmPitch(float angle)
{
	_cameraSpringArmComponent->Pitch(angle);
}

void ACreatureCharacter::VCameraArmYaw(float angle)
{
	_cameraSpringArmComponent->Yaw(angle);
}

void ACreatureCharacter::VCameraZoomInOut(float offset)
{
	_cameraSpringArmComponent->ZoomInOut(offset);
}

FRotator ACreatureCharacter::VGetCameraRotation()
{
	return _cameraComponent->GetComponentRotation();
}

FVector ACreatureCharacter::VGetCameraLocation()
{
	return _cameraComponent->GetComponentLocation();
}

void ACreatureCharacter::VDragCamera(FVector offset)
{
	_cameraComponent->DragCamera(offset);
}

void ACreatureCharacter::VCancelDragCamera()
{
	_cameraComponent->CancelDrag();
}

void ACreatureCharacter::VSetCameraArmPitchLimit(float pitchMin, float pitchMax)
{
	_cameraSpringArmComponent->SetPitchLimit(pitchMin,pitchMax);
}

void ACreatureCharacter::VResetCameraArmPitchLimit()
{
	_cameraSpringArmComponent->ResetPitchLimit();
}

float ACreatureCharacter::VGetCameraArmLength()
{
	return _cameraSpringArmComponent->TargetArmLength;
}

UCameraComponent* ACreatureCharacter::VGetCameraComponent()
{
	return _cameraComponent;
}