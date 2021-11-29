// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HumanCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/PawnCameraComponent.h"
#include "Components/CameraSpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/ActionComponent.h"
#include "Components/AttributeComponent.h"
#include "Projectile/Projectile.h"
#include "Weapon/Weapon.h"


// Sets default values
AHumanCharacter::AHumanCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Create Camera Spring Arm Component
	_cameraSpringArmComponent = CreateDefaultSubobject<UCameraSpringArmComponent>(TEXT("CameraSpringArmComponent"));
	check(_cameraSpringArmComponent != nullptr);
	_cameraSpringArmComponent->SetupAttachment(GetCapsuleComponent());

	// Create a first person camera component.
	_cameraComponent = CreateDefaultSubobject<UPawnCameraComponent>(TEXT("FirstPersonCamera"));
	check(_cameraComponent != nullptr);
	_cameraComponent->SetupAttachment(_cameraSpringArmComponent, USpringArmComponent::SocketName);

	//Create weapon component
	_weaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	check(_weaponComponent != nullptr);

	//Enable the pawn to control camera rotation.
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHumanCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character BeginPlay"));
}

// Called every frame
void AHumanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//walk
	PlayerInputComponent->BindAxis("MoveForward", _actionComponent, &UActionComponent::AddMovementInputX);
	PlayerInputComponent->BindAxis("MoveRight", _actionComponent, &UActionComponent::AddMovementInputY);

	//jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, _actionComponent, &UActionComponent::OnJumpButtonDown);
	PlayerInputComponent->BindAction("Jump", IE_Released, _actionComponent, &UActionComponent::OnJumpButtonUp);

	//Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, _actionComponent, &UActionComponent::OnSprintButtonDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, _actionComponent, &UActionComponent::OnSprintButtonUp);

	//camera
	InputComponent->BindAxis("CameraPitch", _cameraSpringArmComponent, &UCameraSpringArmComponent::Pitch);
	InputComponent->BindAxis("CameraYaw", _cameraSpringArmComponent, &UCameraSpringArmComponent::Yaw);
	InputComponent->BindAxis("ZoomInOut", _cameraSpringArmComponent, &UCameraSpringArmComponent::ZoomInOut);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, _weaponComponent, &UWeaponComponent::OnFireButtonDown);
	PlayerInputComponent->BindAction("Fire", IE_Released, _weaponComponent, &UWeaponComponent::OnFireButtonUp);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, _weaponComponent, &UWeaponComponent::OnAimButtonDown);
	PlayerInputComponent->BindAction("Aim", IE_Released, _weaponComponent, &UWeaponComponent::OnAimButtonUp);
}


UCameraSpringArmComponent* AHumanCharacter::GetSpringArmComponent()
{
	return _cameraSpringArmComponent;
}

UPawnCameraComponent* AHumanCharacter::GetCameraComponent()
{
	return _cameraComponent;
}

UWeaponComponent* AHumanCharacter::GetWeaponComponent()
{
	return _weaponComponent;
}
AWeapon* AHumanCharacter::GetEquippedWeapon()
{
	return _weaponComponent->GetEquipedWeapon();
}