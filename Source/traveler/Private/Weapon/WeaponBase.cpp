// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Character/CreatureCharacter.h"
#include "Components/PoseableMeshComponent.h"
#include "Data/WeaponAnimationModelBase.h"
#include "Components/ExtraTransformProviderComponent.h"
#include "Process/ProcessManagerBase.h"
#include "Interface/ActionInterface.h"
#include "Interface/CharacterCameraInterface.h"
#include "Interface/AnimationCommunicatorInterface.h"
#include "Interface/EventBrokerInterface.h"
#include "Process/ProcessInterface.h"


// Sets default values
AWeaponBase::AWeaponBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Mesh Socket component
	if (_skeletalMeshComponent == nullptr)
	{
		_skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
		check(_skeletalMeshComponent != nullptr);
		SetRootComponent(_skeletalMeshComponent);
	}

	//Create mesh component
	if (_ExtraTransformProviderComponent == nullptr)
	{
		_ExtraTransformProviderComponent = CreateDefaultSubobject<UExtraTransformProviderComponent>(TEXT("ExTransformProviderComponent"));
		check(_ExtraTransformProviderComponent != nullptr);
		_ExtraTransformProviderComponent->Initialize(_skeletalMeshComponent);
	}
	_weaponType = EWeaponType::EWT_None;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	_processManager = NewObject<UProcessManagerBase>(this);
}

void AWeaponBase::VInitialize(ACreatureCharacter* weaponOwner)
{
	_weaponOwner = weaponOwner;
	_ownerActionInterface = Cast<IActionInterface>(_weaponOwner);
	_ownerCameraInterface = Cast<ICharacterCameraInterface>(_weaponOwner);
	_eventBrokerInterface = Cast<IEventBrokerInterface>(_weaponOwner);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_processManager->Tick(DeltaTime);
}

void AWeaponBase::VOnEquipped()
{
}

void AWeaponBase::VOnUnEquipped()
{
	StopAllProcesses();
}

void AWeaponBase::ExecuteProcess(FName processName)
{
	_processManager->ExecutePresetedProcess(processName);
}

void AWeaponBase::StopProcess(FName processName)
{
	_processManager->StopProcess(processName);
}

void AWeaponBase::StopAllProcesses()
{
	_processManager->StopAllProcess();
}

void AWeaponBase::AddToProcessStorage(IProcessInterface* process)
{
	_processManager->AddToProcessPresets(process);
}

bool AWeaponBase::IsProcessRunning(FName processName)
{
	return _processManager->IsProcessRunning(processName);
}

USkeletalMeshComponent* AWeaponBase::GetMeshComponent()
{
	return _skeletalMeshComponent;
}

ACreatureCharacter* AWeaponBase::GetWeaponOwner()
{
	return _weaponOwner;
}

EWeaponType AWeaponBase::GetWeaponType()
{
	return _weaponType;
}


void AWeaponBase::VReset()
{
}

EAnimationState AWeaponBase::GetOwnerAnimationState()
{
	return _characterAnimationState;
}

IActionInterface* AWeaponBase::GetOwnerActionInterface()
{
	return _ownerActionInterface;
}

ICharacterCameraInterface* AWeaponBase::GetOwnerCameraInterface()
{
	return _ownerCameraInterface;
}

IEventBrokerInterface* AWeaponBase::GetEventBrokerInterface()
{
	return _eventBrokerInterface;
}

void AWeaponBase::VWeaponControlButtonA()
{
}

void AWeaponBase::VWeaponControlButtonB()
{
}

void AWeaponBase::VWeaponControlButtonC()
{
}

void AWeaponBase::VWeaponControlButtonD()
{
}

bool AWeaponBase::VTryGetSocketName(ETransform transformType, FName& outSocketName)
{
	return _ExtraTransformProviderComponent->VTryGetSocketName(transformType, outSocketName);
}

bool AWeaponBase::VTryGetTransform(ETransform meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform)
{
	return _ExtraTransformProviderComponent->TryGetTransform(meshSocketType, transformSpace, outTransform);
}

void AWeaponBase::VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState)
{
	_characterAnimationState = newState;
}