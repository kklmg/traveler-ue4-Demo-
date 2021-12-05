// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/Weapon.h"
#include "Weapon/Bow.h"
#include "Character/HumanCharacter.h"

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
		bow->VInitialize(GetOwner<AHumanCharacter>());
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
		_aWeapon->OnFireButtonPress(DeltaTime);
	}

	if (_aWeapon != nullptr && _isAiming)
	{
		_aWeapon->OnAimButtonPress(DeltaTime);
	}
}

void UWeaponComponent::SetWeapon(AWeapon* weapon)
{
	if (_aWeapon != weapon && _isFiring == false && _isAiming == false)
	{
		_aWeapon = weapon;

		OnWeaponChanged.Broadcast(_aWeapon);

		//Get Character
		AHumanCharacter* character = Cast<AHumanCharacter>(GetOwner());
		check(character != nullptr);

		//Attach Weapon 
		FName leftHandSocketName = character->GetMeshSocketNameByType(EMeshSocketType::MST_LeftHand);		

		_aWeapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, leftHandSocketName);
		//_aWeapon->AttachToActor(character, FAttachmentTransformRules::KeepRelativeTransform, leftHandSocketName);
		
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
		_aWeapon->SetIsReadyToFire(false);
		_aWeapon->OnFireButtonDown();
		OnWeaponFireStart.Broadcast(_aWeapon);
	}
}

void UWeaponComponent::OnFireButtonUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "left mouse up");
	if (_aWeapon && _isFiring == true)
	{
		_aWeapon->OnFireButtonUp();
		OnWeaponFireEnd.Broadcast(_aWeapon);
		_isFiring = false;
		//_aWeapon->IsReadyToFire();
	}
}

void UWeaponComponent::OnAimButtonDown()
{
	if (_aWeapon)
	{
		_aWeapon->OnAimButtonDown();
		OnWeaponAimStart.Broadcast(_aWeapon);
		_isFiring = false;
	}

	_isAiming = true;
}
void UWeaponComponent::OnAimButtonUp()
{
	if (_aWeapon)
	{
		_aWeapon->OnAimButtonUp();
		OnWeaponAimEnd.Broadcast(_aWeapon);
		_isAiming = false;
	}
}

void UWeaponComponent::OnAnimFrameStart_Fire()
{
	if (_aWeapon) 
	{
		_aWeapon->OnEnterAnimFrame_Launch();
	}
}

void UWeaponComponent::OnAnimFrameStart_FireReady() 
{
	if (_aWeapon)
	{
		_aWeapon->SetIsReadyToFire(true);
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





