// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Character/CreatureCharacter.h"
#include "Data/WeaponAnimationModelBase.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Components/ExtraTransformProviderComponent.h"
#include "Components/ActionComponent.h"
#include "Process/ProcessManagerBase.h"
#include "Interface/CharacterCameraInterface.h"
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
		check(_skeletalMeshComponent);
		SetRootComponent(_skeletalMeshComponent);
	}

	//Create mesh component
	if (_extraTransformProviderComp == nullptr)
	{
		_extraTransformProviderComp = CreateDefaultSubobject<UExtraTransformProviderComponent>(TEXT("ExTransformProviderComponent"));
		check(_extraTransformProviderComp);
		_extraTransformProviderComp->Initialize(_skeletalMeshComponent);
	}
	_weaponType = EWeaponType::EWT_None;
}

void AWeaponBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	_processManager = NewObject<UProcessManagerBase>(this);
	_weaponAnimationModel = NewObject<UWeaponAnimationModelBase>(this);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::VInitialize(ACreatureCharacter* weaponOwner)
{
	_weaponOwner = weaponOwner;
	check(_weaponOwner);
	
	_ownerActionComp = Cast<UActionComponent>(_weaponOwner->GetComponentByClass(UActionComponent::StaticClass()));
	check(weaponOwner);

	_ownerEventBrokerComp = Cast<UEventBrokerComponent>(_weaponOwner->GetComponentByClass(UEventBrokerComponent::StaticClass()));
	check(_ownerEventBrokerComp);

	_ownerExtraTransformProviderComp = Cast<UExtraTransformProviderComponent>(_weaponOwner->GetComponentByClass(UExtraTransformProviderComponent::StaticClass()));
	check(_ownerExtraTransformProviderComp);

	_ownerCameraInterface = Cast<ICharacterCameraInterface>(_weaponOwner);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_processManager->Tick(DeltaTime);
}

void AWeaponBase::VOnEquipped()
{
	OnWeaponEquipped.Broadcast(this);
}

void AWeaponBase::VOnUnEquipped()
{
	OnWeaponUnequipped.Broadcast(this);

	StopAllProcesses();
	_weaponAnimationModel->ClearData();
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

FORCEINLINE_DEBUGGABLE USkeletalMeshComponent* AWeaponBase::GetMeshComponent()
{
	return _skeletalMeshComponent;
}

FORCEINLINE_DEBUGGABLE ACreatureCharacter* AWeaponBase::GetWeaponOwner()
{
	return _weaponOwner;
}

FORCEINLINE_DEBUGGABLE EWeaponType AWeaponBase::GetWeaponType()
{
	return _weaponType;
}


void AWeaponBase::VReset()
{
}

FORCEINLINE_DEBUGGABLE EAnimationState AWeaponBase::GetOwnerAnimationState()
{
	return _characterAnimationState;
}

FORCEINLINE_DEBUGGABLE UActionComponent* AWeaponBase::GetOwnerActionComp()
{
	return _ownerActionComp;
}

FORCEINLINE_DEBUGGABLE UExtraTransformProviderComponent* AWeaponBase::GetExTransformProviderComp()
{
	return _extraTransformProviderComp;
}

FORCEINLINE_DEBUGGABLE UExtraTransformProviderComponent* AWeaponBase::GetOwnerExTransformProviderComp()
{
	return _ownerExtraTransformProviderComp;
}

FORCEINLINE_DEBUGGABLE ICharacterCameraInterface* AWeaponBase::GetOwnerCameraInterface()
{
	return _ownerCameraInterface;
}

FORCEINLINE_DEBUGGABLE UEventBrokerComponent* AWeaponBase::GetOwnerEventBrokerComp()
{
	return _ownerEventBrokerComp;
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

void AWeaponBase::VOnCharacterAnimationStateChanged(EAnimationState prevState, EAnimationState newState)
{
	_characterAnimationState = newState;
}

FORCEINLINE UWeaponAnimationModelBase* AWeaponBase::GetWeaponAnimationModel()
{
	return _weaponAnimationModel;
}
