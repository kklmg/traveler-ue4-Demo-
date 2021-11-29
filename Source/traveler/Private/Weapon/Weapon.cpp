// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Character/HumanCharacter.h"
#include "Components/PoseableMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_isReadyToFire = false;
	WeaponType = EWeaponType::WT_UnKnown;

	_skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	//_poseableMeshComponent = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComponent"));
	SetRootComponent(_skeletalMeshComponent);
	//_poseableMeshComponent->attac
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::Initialize(AHumanCharacter* weaponOwner)
{
	_weaponOwner = weaponOwner;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USkeletalMeshComponent* AWeapon::GetMeshComponent()
{
	return _skeletalMeshComponent;
}



AHumanCharacter* AWeapon::GetWeaponOwner()
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

void AWeapon::OnFireButtonPress(float deltaTime){}
void AWeapon::OnFireButtonUp() {}
void AWeapon::OnAimButtonDown() {}
void AWeapon::OnAimButtonPress(float deltaTime) {}
void AWeapon::OnAimButtonUp() {}

void AWeapon::OnEnterAnimFrame_ReloadStart() {}
void AWeapon::OnTickAnimFrame_Reloading() {}
void AWeapon::OnEnterAnimFrame_ReloadCompleted() {}
void AWeapon::OnEnterAnimFrame_Launch(){}

FTransform AWeapon::GetMuzzleTransform()
{
	return FTransform::Identity;
}
