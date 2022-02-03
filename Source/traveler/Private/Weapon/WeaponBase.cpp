// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"
#include "Character/CreatureCharacter.h"
#include "Components/PoseableMeshComponent.h"
#include "Data/WeaponAnimationModelBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_isReadyToFire = false;
	WeaponType = EWeaponType::EWT_None;

	_skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SetRootComponent(_skeletalMeshComponent);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

void AWeaponBase::VInitialize(ACreatureCharacter* weaponOwner)
{
	_weaponOwner = weaponOwner;
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USkeletalMeshComponent* AWeaponBase::GetMeshComponent()
{
	return _skeletalMeshComponent;
}

ACreatureCharacter* AWeaponBase::GetWeaponOwner()
{
	return _weaponOwner;
}

//UWeaponAnimationModelBase* AWeaponBase::GetAnimationModel()
//{
//	return _animationModel;
//}


void AWeaponBase::StartFiring()
{
	if (VTMCanFire() && _isFiring == false)
	{
		_isFiring = true;
		VTMStartFiring();
	}
}
void AWeaponBase::FiringInProgress(float deltaTime)
{
	if (_isFiring)
	{
		VTMFiringInProgress(deltaTime);
	}
}
void AWeaponBase::StopFiring()
{
	if (_isFiring)
	{
		_isFiring = false;
		VTMStopFiring();
	}
}

void AWeaponBase::StarAiming()
{
	if (VTMCanAim() && _isAiming == false) 
	{
		_isAiming = true;
		VTMStarAiming();
	}
}
void AWeaponBase::AimingInProgress(float deltaTime)
{
	if (_isAiming)
	{
		VTMAimingInProgress(deltaTime);
	}
}
void AWeaponBase::StopAiming()
{
	if (_isAiming)
	{
		_isAiming = false;
		VTMStopAiming();
	}
}

void AWeaponBase::StopAllActions()
{
	StopFiring();
	StopAiming();
}

bool AWeaponBase::IsFiring()
{
	return _isFiring;
}
bool AWeaponBase::IsAiming()
{
	return _isAiming;
}