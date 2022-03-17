// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CreatureCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActionComponent.h"
#include "Data/CharacterAttribute.h"
#include "Components/AttributeComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BillBoardWidgetComponent.h"
#include "Components/AnimationEventComponent.h"
#include "Components/StateComponent.h"
#include "Components/PawnCameraComponent.h"
#include "Components/CameraSpringArmComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/MeshSocketComponent.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Components/IKComponent.h"
#include "Components/DamageHandlerComponent.h"
#include "Input/InputHandlerComponent.h"
#include "Components/DamageHandlerComponent.h"


ACreatureCharacter::ACreatureCharacter(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	//Create State component
	if (_stateComponent == nullptr)
	{
		_stateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
		check(_stateComponent != nullptr);
	}
	//Create Attribute component
	if (_attributeComponent == nullptr)
	{
		_attributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
		check(_attributeComponent != nullptr);
	}
	
	//Create Mesh Socket component
	if (_meshSocketComponent == nullptr)
	{
		_meshSocketComponent = CreateDefaultSubobject<UMeshSocketComponent>(TEXT("MeshSocketComponent"));
		check(_meshSocketComponent != nullptr);
		_meshSocketComponent->Initialize(GetMesh());
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
	//Create billboard component
	if (_billboardWidgetComponent == nullptr)
	{
		_billboardWidgetComponent = CreateDefaultSubobject<UBillBoardWidgetComponent>(TEXT("BillBoardWidgetComponent"));
		check(_billboardWidgetComponent != nullptr);
	}
	//Create Animation Event component
	if (_animationEventComponent == nullptr)
	{
		_animationEventComponent = CreateDefaultSubobject<UAnimationEventComponent>(TEXT("AnimationEventComponent"));
		check(_billboardWidgetComponent != nullptr);
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
}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();

	
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

FORCEINLINE UAttributeComponent* ACreatureCharacter::GetAttributeComponent()
{
	return _attributeComponent;
}

FORCEINLINE UAnimationEventComponent* ACreatureCharacter::GetAnimationEventComponent()
{
return _animationEventComponent;
}

FORCEINLINE UCharacterAttribute* ACreatureCharacter::VGetAttribute(EAttributeType attributeType)
{
	return _attributeComponent->GetAttribute(attributeType);
}

bool ACreatureCharacter::VSetAttribute(EAttributeType attributeType, float newValue)
{
	return _attributeComponent->SetAttribute(attributeType, newValue);
}

bool ACreatureCharacter::VSetAttributeChange(EAttributeType attributeType, float deltaValue)
{
	return _attributeComponent->SetAttributeChange(attributeType, deltaValue);
}

bool ACreatureCharacter::VCanConsume(UCostData* cost)
{
	return _attributeComponent->CanConsume(cost);
}

bool ACreatureCharacter::VTryConsume(UCostData* cost)
{
	return _attributeComponent->TryConsume(cost);
}

FORCEINLINE UActionComponent* ACreatureCharacter::GetActionComponent()
{
	return _actionComponent;
}

UActionBase* ACreatureCharacter::VExecuteAction(EActionType actionType)
{
	if (_actionComponent) 
	{
		return _actionComponent->ExecuteAction(actionType);
	}
	return nullptr;
}


FORCEINLINE UActionBlackBoard* ACreatureCharacter::VGetActionBlackBoard()
{
	return _actionComponent->GetActionBlackBoard();
}

bool ACreatureCharacter::VCheckActionIsInProgress(EActionType actionType)
{
	return _actionComponent->CheckActionIsInProgress(actionType);
}

FStateData ACreatureCharacter::VGetStateData()
{
	return _stateComponent->VGetStateData();
}

void ACreatureCharacter::VSetSituationState(ESituationState newState)
{
	_stateComponent->VSetSituationState(newState);
}


void ACreatureCharacter::VSetHealthState(EHealthState newState)
{
	_stateComponent->VSetHealthState(newState);
}

void ACreatureCharacter::VSetPostureState(EPostureState newState)
{
	_stateComponent->VSetPostureState(newState);
}

void ACreatureCharacter::VSetAnimationState(EAnimationState newState)
{
	_stateComponent->VSetAnimationState(newState);
}

EAnimationState ACreatureCharacter::VGetAnimationState()
{
	return _stateComponent->VGetAnimationState();
}

FOnSituationStateChanged* ACreatureCharacter::VGetSituationStateChangedDelegate()
{
	return _stateComponent->VGetSituationStateChangedDelegate();
}

FOnHealthStateChanged* ACreatureCharacter::VGetHealthStateChangedDelegate()
{
	return _stateComponent->VGetHealthStateChangedDelegate();
}

FOnPostureStateChanged* ACreatureCharacter::VGetPostureStateChangedDelegate()
{
	return _stateComponent->VGetPostureStateChangedDelegate();
}

FOnAnyStateChanged* ACreatureCharacter::VGetAnyStateChangedDelegate()
{
	return _stateComponent->VGetAnyStateChangedDelegate();
}

FOnAnimationStateChanged* ACreatureCharacter::VGetAnimationStateChangedDelegate()
{
	return _stateComponent->VGetAnimationStateChangedDelegate();
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

void ACreatureCharacter::VEquipWeapon(AWeaponBase* weapon)
{
	_weaponComponent->EquipWeapon(weapon);
}

AWeaponBase* ACreatureCharacter::VGetEquipedWeapon()
{
	return _weaponComponent->GetEquipedWeapon();
}

void ACreatureCharacter::VExecuteWeaponProcess(FName weaponProcessName)
{
	_weaponComponent->ExecuteWeaponProcess(weaponProcessName);
}

void ACreatureCharacter::VStopWeaponProcess(FName weaponProcessName)
{
	_weaponComponent->StopWeaponProcess(weaponProcessName);
}

void ACreatureCharacter::VStopAllProcess()
{
	_weaponComponent->StopAllWeaponProcesses();
}

FAnimationModel ACreatureCharacter::VGetAnimationModel()
{
	return _animationModel;
}

FAnimationModel& ACreatureCharacter::VGetAnimationModelRef()
{
	return _animationModel;
}

void ACreatureCharacter::VHandleDamage(UMyDamageType* damageType, FHitResult hitResult)
{
	_damageHandlerComponent->HandleDamage(damageType, hitResult);
}

void ACreatureCharacter::VShowWidget(EActorUI widgeType)
{
	_billboardWidgetComponent->ShowWidget(widgeType);
}

void ACreatureCharacter::VHideWidget(EActorUI widgeType)
{
	_billboardWidgetComponent->HideWidget(widgeType);
}

FName ACreatureCharacter::GetMeshSocketNameByType(EMeshSocketType meshSocketType)
{
	return _meshSocketComponent->GetMeshSocketNameByType(meshSocketType);
}

bool ACreatureCharacter::VTryGetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform)
{
	return _meshSocketComponent->TryGetMeshSocketTransform(meshSocketType,transformSpace,outTransform);
}