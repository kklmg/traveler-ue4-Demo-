// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/WeaponBase.h"
#include "Weapon/BowBase.h"
#include "Character/CreatureCharacter.h"
#include "Interface/ExtraTransformProvider.h"
#include "Interface/AnimationCommunicatorInterface.h"

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

	IAnimationCommunicatorInterface* animationCommunicator = GetOwner<IAnimationCommunicatorInterface>();
	if(animationCommunicator)
	{
		_animationViewModel = animationCommunicator->VGetAnimationModel();
	}

	if (DefaultWeaponClass)
	{
		//FActorSpawnParameters params;
		AWeaponBase* bow = GetWorld()->SpawnActor<AWeaponBase>(DefaultWeaponClass);
		bow->VInitialize(GetOwner<ACreatureCharacter>());
		EquipWeapon(bow);
	}

	_animationCommunicator = GetOwner<IAnimationCommunicatorInterface>();
	if (_animationCommunicator)
	{
		OnAnimationStateChanged(_animationCommunicator->VGetAnimationState(), _animationCommunicator->VGetAnimationState());
		_animationCommunicator->VGetAnimationStateChangedDelegate().AddDynamic(this, &UWeaponComponent::OnAnimationStateChanged);
	}
	// ...
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponComponent::ExecuteWeaponProcess(FName processName)
{
	if (_weaponIns)
	{
		_weaponIns->ExecuteProcess(processName);
	}
}

void UWeaponComponent::StopWeaponProcess(FName processName)
{
	if (_weaponIns)
	{
		_weaponIns->StopProcess(processName);
	}
}

void UWeaponComponent::StopAllWeaponProcesses()
{
	if (_weaponIns)
	{
		_weaponIns->StopAllProcesses();
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

		OnWeaponChanged.Broadcast(_weaponIns);

		if(_animationViewModel)
		{
			_animationViewModel->SetUObject(AnimationDataKey::objWeapon,_weaponIns);
		}

		//try attach weapon to hands ------------------------------------------------------------

		//Get Character
		ACreatureCharacter* character = GetOwner<ACreatureCharacter>();
		check(character != nullptr);

		//get left hand socket name
		FName leftHandSocketName;
		character->VTryGetSocketName(ETransform::ETransform_LeftHand, leftHandSocketName);

		//Attach Weapon 
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
	return _weaponIns ? _weaponIns->IsProcessRunning(WeaponProcessName::FIRE) : false;
}

bool UWeaponComponent::IsAiming()
{
	return _weaponIns ? _weaponIns->IsProcessRunning(WeaponProcessName::AIM) : false;
}

void UWeaponComponent::OnAnimationStateChanged(EAnimationState prevState, EAnimationState newState)
{
	if(_weaponIns)
	{
		_weaponIns->VOnCharacterAnimationStateChanged(prevState, newState);
	}
}





