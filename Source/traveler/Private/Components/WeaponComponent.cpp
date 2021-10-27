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


	if (DefaultWeapon) 
	{
		FActorSpawnParameters params;
		AWeapon* bow = GetWorld()->SpawnActor<AWeapon>(DefaultWeapon);
		SetWeapon(bow);

		
	}
	// ...

	
	

}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::SetWeapon(AWeapon* weapon)
{
	if (_aWeapon != weapon)
	{
		_aWeapon = weapon;

		//Get Character
		ACharacter* character = Cast<ACharacter>(GetOwner());
		check(character != nullptr);

		//Attach Weapon 
		_aWeapon->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketLeftHand);
	}
}

void UWeaponComponent::SetArmWeapon(bool isArmed) 
{
	if (_aWeapon)
	{
		_aWeapon->SetActorHiddenInGame(isArmed);
	}
}


