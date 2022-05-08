// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Components/EventBrokerComponent.h"
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

	_eventBrokerComp = Cast<UEventBrokerComponent>(GetOwner()->GetComponentByClass(UEventBrokerComponent::StaticClass()));
}

void UWeaponComponent::OnReceiveEvent_LifeStateChanged(UObject* baseData)
{
	auto eventData = Cast<NSEvent::ActorLifeStateChanged::DataType>(baseData);
	if (eventData && eventData->Value == false)
	{
		StopAllWeaponProcesses();
	}
}

void UWeaponComponent::BindInputs(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("WeaponButtonA", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonA);
	PlayerInputComponent->BindAction("WeaponButtonB", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonB);
	PlayerInputComponent->BindAction("WeaponButtonC", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonC);
	PlayerInputComponent->BindAction("WeaponButtonD", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonD);
	PlayerInputComponent->BindAction("WeaponButtonE", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonE);
	PlayerInputComponent->BindAction("WeaponButtonF", IE_Pressed, this, &UWeaponComponent::WeaponControlButtonF);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_ownerExTransformProviderComp = Cast<UExTransformProviderComponent>(GetOwner()->GetComponentByClass(UExTransformProviderComponent::StaticClass()));

	UAnimControlComponent* animControlComp = Cast<UAnimControlComponent>(GetOwner()->GetComponentByClass(UAnimControlComponent::StaticClass()));
	if (animControlComp)
	{
		_animationViewModel = animControlComp->GetAnimationModel();
	}

	if (DefaultWeaponClass)
	{
		//FActorSpawnParameters params;
		AWeaponBase* bow = GetWorld()->SpawnActor<AWeaponBase>(DefaultWeaponClass);
		bow->VInitialize(GetOwner<ACreatureCharacter>());
		EquipWeapon(bow);
	}

	if (animControlComp)
	{
		OnAnimationStateChanged(animControlComp->GetAnimationState(), animControlComp->GetAnimationState());
		animControlComp->GetAnimationStateChangedDelegate().AddDynamic(this, &UWeaponComponent::OnAnimationStateChanged);
	}
	
	if (_eventBrokerComp)
	{
		_eventBrokerComp->SubscribeEvent(NSEvent::ActorLifeStateChanged::Name,this, &UWeaponComponent::OnReceiveEvent_LifeStateChanged);
	}
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UProcessBase* UWeaponComponent::GetWeaponProcess(FName processName)
{
	return _weaponIns ? _weaponIns->GetProcess(processName) : nullptr;
}

void UWeaponComponent::ExecuteWeaponProcess(FName processName)
{
	if (_weaponIns)
	{
		_weaponIns->ExecuteProcess(processName);
	}
}

void UWeaponComponent::TickWeaponProcess(FName processName, float deltaTime)
{
	if (_weaponIns)
	{
		_weaponIns->TickProcess(processName,deltaTime);
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

		if(_animationViewModel)
		{
			_animationViewModel->SetUObject(NSAnimationDataKey::objWeapon,_weaponIns);
		}

		OnWeaponChanged.Broadcast(_weaponIns);
	

		//try attach weapon to hands ------------------------------------------------------------

		//get left hand socket name
		FName outLeftHandSocketName;
		if(_ownerExTransformProviderComp)
		{
			_ownerExTransformProviderComp->TryGetSocketName(ETransform::ETransform_LeftHand, outLeftHandSocketName);
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

void UWeaponComponent::WeaponControlButtonE()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlButtonE();
	}
}

void UWeaponComponent::WeaponControlButtonF()
{
	if (_weaponIns)
	{
		_weaponIns->VWeaponControlButtonF();
	}
}

AWeaponBase* UWeaponComponent::GetEquipedWeapon()
{
	return _weaponIns;
}

bool UWeaponComponent::IsFiring()
{
	return _weaponIns ? _weaponIns->IsProcessRunning(NSNameWeaponProcess::FIRE) : false;
}

bool UWeaponComponent::IsAiming()
{
	return _weaponIns ? _weaponIns->IsProcessRunning(NSNameWeaponProcess::AIM) : false;
}

void UWeaponComponent::OnAnimationStateChanged(EAnimationState prevState, EAnimationState newState)
{
	if(_weaponIns)
	{
		_weaponIns->VOnCharacterAnimationStateChanged(prevState, newState);
	}
}





