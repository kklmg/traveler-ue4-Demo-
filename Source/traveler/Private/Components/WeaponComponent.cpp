// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Components/ActionComponent.h"
#include "Data/AnimationModelBase.h"
#include "Weapon/WeaponBase.h"
#include "Weapon/BowBase.h"
#include "Process/ProcessBase.h"
#include "Character/CreatureCharacter.h"

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

	_actionComp = Cast<UActionComponent>(GetOwner()->GetComponentByClass(UActionComponent::StaticClass()));
	_animControlComp = Cast<UAnimControlComponent>(GetOwner()->GetComponentByClass(UAnimControlComponent::StaticClass()));
	_ownerExTransformProviderComp = Cast<UExTransformProviderComponent>(GetOwner()->GetComponentByClass(UExTransformProviderComponent::StaticClass()));
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (DefaultWeaponClass)
	{
		//FActorSpawnParameters params;
		AWeaponBase* bow = GetWorld()->SpawnActor<AWeaponBase>(DefaultWeaponClass);
		bow->VInitialize(GetOwner<ACreatureCharacter>());
		EquipWeapon(bow);
	}
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_weaponIns)
	{
		_weaponIns->OnWeaponCompTick(DeltaTime);
	}
}


void UWeaponComponent::EquipWeapon(AWeaponBase* newWeapon)
{
	if (_weaponIns != newWeapon && newWeapon)
	{
		if (_weaponIns)
		{
			_weaponIns->VOnUnEquipped();
		}

		_weaponIns = newWeapon;
		_weaponIns->VOnEquipped();

		if(_actionComp)
		{
			if (_weaponIns)
			{
				_actionComp->RegisterActionPresetGroup(EActionPrestGroup::EACTPresetGroup_WeaponActions,_weaponIns->GetActionPresetGroupClass());
				_actionComp->SwitchActionPresetGroup(EActionPrestGroup::EACTPresetGroup_WeaponActions);
			}
			else
			{
				_actionComp->SwitchActionPresetGroup(EActionPrestGroup::EACTPresetGroup_BasicActions);
			}
		}

		if(_animControlComp && _animControlComp->GetAnimationModel())
		{
			_animControlComp->GetAnimationModel()->SetUObject(NSAnimationDataKey::objWeapon,_weaponIns);
		}

		OnWeaponChanged.Broadcast(_weaponIns);
	

		//try attach weapon to hands ------------------------------------------------------------

		//get left hand socket name
		FName outLeftHandSocketName;
		if(_ownerExTransformProviderComp)
		{
			_ownerExTransformProviderComp->TryGetSocketName(ETransformType::ETransform_LeftHand, outLeftHandSocketName);
		}

		//Get Character
		ACreatureCharacter* character = GetOwner<ACreatureCharacter>();
		check(character != nullptr);

		//Attach Weapon to character
		_weaponIns->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, outLeftHandSocketName);
	}
}

void UWeaponComponent::TakeOutWeapon(bool isTakeOut)
{
	if (_weaponIns)
	{
		_weaponIns->SetActorHiddenInGame(!isTakeOut);
	}
}


void UWeaponComponent::WeaponControlA()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlA();
	}
}

void UWeaponComponent::WeaponControlB()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlB();
	}
}

void UWeaponComponent::WeaponControlC()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlC();
	}
}

void UWeaponComponent::WeaponControlD()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlD();
	}
}

void UWeaponComponent::WeaponControlE()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlE();
	}
}

void UWeaponComponent::WeaponControlF()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlF();
	}
}

AWeaponBase* UWeaponComponent::GetEquipedWeapon()
{
	return _weaponIns;
}