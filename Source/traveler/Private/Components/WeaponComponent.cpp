// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/Weapon.h"
#include "Weapon/Bow.h"
#include "Character/MyCharacter.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();


	if (DefaultWeaponClass)
	{
		//FActorSpawnParameters params;
		AWeapon* bow = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
		bow->Initialize(Cast<AMyCharacter>(GetOwner()));
		SetWeapon(bow);
	}
	// ...
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (_aWeapon != nullptr && _isFiring)
	{
		_aWeapon->FiringInProgress(DeltaTime);
	}

	if (_aWeapon != nullptr && _isAiming)
	{
		_aWeapon->AimmingInProgress(DeltaTime);
	}
}

void UWeaponComponent::SetWeapon(AWeapon* weapon)
{
	if (_aWeapon != weapon && _isFiring == false && _isAiming == false)
	{
		_aWeapon = weapon;

		OnWeaponChanged.Broadcast(_aWeapon);

		//Get Character
		ACharacter* character = Cast<ACharacter>(GetOwner());
		check(character != nullptr);

		//Attach Weapon 
		_aWeapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketLeftHand);
	}
}

void UWeaponComponent::SetWhetherEquipWeapon(bool isEquiped)
{
	if (_aWeapon)
	{
		_aWeapon->SetActorHiddenInGame(isEquiped);
	}
}


void UWeaponComponent::OnFireButtonDown() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "left mouse dowm");
	if (_aWeapon && _aWeapon->IsReadyToFire())
	{
		_isFiring = true;
		_aWeapon->OnFireStart();
		OnWeaponFireStart.Broadcast(_aWeapon);
	}
}

void UWeaponComponent::OnFireButtonUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "left mouse up");
	if (_aWeapon && _isFiring == true)
	{
		_aWeapon->OnFireEnd();
		OnWeaponFireEnd.Broadcast(_aWeapon);
		_isFiring = false;
		//_aWeapon->IsReadyToFire();
	}
}

void UWeaponComponent::OnAimButtonDown()
{
	if (_aWeapon)
	{
		_aWeapon->OnAimStart();
		OnWeaponAimStart.Broadcast(_aWeapon);
		_isFiring = false;
	}

	_isAiming = true;
}
void UWeaponComponent::OnAimButtonUp()
{
	if (_aWeapon)
	{
		_aWeapon->OnAimEnd();
		OnWeaponAimEnd.Broadcast(_aWeapon);
		_isAiming = false;
	}
}

void UWeaponComponent::OnAnimFrameStart_Fire()
{
	if (_aWeapon) 
	{
		_aWeapon->OnAnimFrameStart_Fire();
	}
}

AWeapon* UWeaponComponent::GetEquipedWeapon()
{
	return _aWeapon;
}

bool UWeaponComponent::IsFiring()
{
	return _isFiring;
}
bool UWeaponComponent::IsAiming()
{
	return _isAiming;
}





