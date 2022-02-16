// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/WeaponBase.h"
#include "Weapon/BowBase.h"
#include "Character/CreatureCharacter.h"
#include "Interface/AnimationModelProvider.h"
#include "Interface/StateInterface.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
	bWantsInitializeComponent = true;
	
}


void UWeaponComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UWeaponComponent::BindInputs(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("WeaponButtonA", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonA);
	PlayerInputComponent->BindAction("WeaponButtonB", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonB);
	PlayerInputComponent->BindAction("WeaponButtonC", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonC);
	PlayerInputComponent->BindAction("WeaponButtonD", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonD);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	_animationModelProvider = GetOwner<IAnimationModelProvider>();
	_stateInterface = GetOwner<IStateInterface>();

	if (DefaultWeaponClass)
	{
		//FActorSpawnParameters params;
		AWeaponBase* bow = GetWorld()->SpawnActor<AWeaponBase>(DefaultWeaponClass);
		bow->VInitialize(GetOwner<ACreatureCharacter>());
		EquipWeapon(bow);
	}

	if (_stateInterface)
	{
		OnAnimationStateChanged(_stateInterface->VGetAnimationState(), _stateInterface->VGetAnimationState());
		_stateInterface->VGetAnimationStateChangedDelegate()->AddDynamic(this, &UWeaponComponent::OnAnimationStateChanged);
	}

	// ...
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (_weaponIns)
	{
		_weaponIns->FiringInProgress(DeltaTime);
		_weaponIns->AimingInProgress(DeltaTime);
	}
	if(_animationModelProvider)
	{
		_animationModelProvider->VGetAnimationModelRef().weapon = _weaponIns;	
		_animationModelProvider->VGetAnimationModelRef().bIsWeaponFiring = _weaponIns ? _weaponIns->IsFiring() : false;
		_animationModelProvider->VGetAnimationModelRef().bIsWeaponAiming = _weaponIns ? _weaponIns->IsAiming() : false;
	}
}

void UWeaponComponent::EquipWeapon(AWeaponBase* newWeapon)
{
	if (_weaponIns != newWeapon && newWeapon)
	{
		if (_weaponIns)
		{
			_weaponIns->StopAllActions();
		}

		_weaponIns = newWeapon;

		OnWeaponChanged.Broadcast(_weaponIns);

		//Get Character
		ACreatureCharacter* character = GetOwner<ACreatureCharacter>();
		check(character != nullptr);

		//Attach Weapon 
		FName leftHandSocketName = character->GetMeshSocketNameByType(EMeshSocketType::MST_LeftHand);		
		_weaponIns->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, leftHandSocketName);
	}
}

void UWeaponComponent::TakeOutWeapon(bool isTakeOut)
{
	if (_weaponIns)
	{
		_weaponIns->SetActorHiddenInGame(!isTakeOut);
	}
}


void UWeaponComponent::StartFiring() 
{
	if (_weaponIns)
	{
		_weaponIns->StartFiring();
	}
	if (_animationModelProvider)
	{
		_animationModelProvider->VGetAnimationModelRef().bIsWeaponFiring = true;
	}
}

void UWeaponComponent::StopFiring()
{
	if (_weaponIns)
	{
		_weaponIns->StopFiring();
		OnWeaponFireEnd.Broadcast(_weaponIns);
	}
	if (_animationModelProvider)
	{
		_animationModelProvider->VGetAnimationModelRef().bIsWeaponFiring = false;
	}
}

void UWeaponComponent::StartAiming()
{
	if (_weaponIns)
	{
		_weaponIns->StarAiming();
		OnWeaponAimStart.Broadcast(_weaponIns);
	}
	if (_animationModelProvider)
	{
		_animationModelProvider->VGetAnimationModelRef().bIsWeaponAiming = true;
	}
}
void UWeaponComponent::StopAiming()
{
	if (_weaponIns)
	{
		_weaponIns->StopAiming();
		OnWeaponAimEnd.Broadcast(_weaponIns);
	}
	if (_animationModelProvider)
	{
		_animationModelProvider->VGetAnimationModelRef().bIsWeaponAiming = false;
	}
}

void UWeaponComponent::WeaponControlButtonA()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlButtonA();
	}
}

void UWeaponComponent::WeaponControlButtonB()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlButtonB();
	}
}

void UWeaponComponent::WeaponControlButtonC()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlButtonC();
	}
}

void UWeaponComponent::WeaponControlButtonD()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlButtonD();
	}
}

AWeaponBase* UWeaponComponent::GetEquipedWeapon()
{
	return _weaponIns;
}

bool UWeaponComponent::IsFiring()
{
	if(_weaponIns)
	{
		return _weaponIns->IsFiring();
	}
	return false;
}
bool UWeaponComponent::IsAiming()
{
	if (_weaponIns)
	{
		return _weaponIns->IsAiming();
	}
	return false;
}

void UWeaponComponent::OnAnimationStateChanged(EAnimationState prevState, EAnimationState newState)
{
	if(_weaponIns)
	{
		_weaponIns->VOnCharacterAnimationStateChanged(prevState, newState);
	}
}





