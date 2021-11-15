// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Character/MyCharacter.h"
#include "Components/PoseableMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_isReadyToFire = false;

	//_skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	_poseableMeshComponent = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComponent"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Initialize(AMyCharacter* weaponOwner)
{
	_weaponOwner = weaponOwner;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//USkeletalMeshComponent* AWeapon::GetMeshComponent()
//{
//	return _skeletalMeshComponent;
//}



AMyCharacter* AWeapon::GetWeaponOwner() 
{
	return _weaponOwner;
}

void AWeapon::SetIsReadyToFire(bool fireable)
{
	_isReadyToFire = fireable;
}

bool AWeapon::IsReadyToFire() 
{
	return _isReadyToFire;
}

void AWeapon::FiringInProgress(float deltaTime){}
void AWeapon::OnFireEnd() {}
void AWeapon::OnAimStart() {}
void AWeapon::AimmingInProgress(float deltaTime) {}
void AWeapon::OnAimEnd() {}

void AWeapon::OnEnterAnimFrame_ReloadStart() {}
void AWeapon::OnTickAnimFrame_Reloading() {}
void AWeapon::OnEnterAnimFrame_ReloadCompleted() {}
void AWeapon::OnEnterAnimFrame_Launch(){}
