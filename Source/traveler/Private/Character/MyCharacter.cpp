// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MyCharacter.h"
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
AMyCharacter::AMyCharacter()
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

	//Create action component
	_actionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
	check(_actionComponent != nullptr);

	//Create weapon component
	_weaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	check(_weaponComponent != nullptr);

	//Create Attribute component
	_attributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	check(_attributeComponent != nullptr);

	//Enable the pawn to control camera rotation.
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character BeginPlay"));
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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


UCameraSpringArmComponent* AMyCharacter::GetSpringArmComponent()
{
	return _cameraSpringArmComponent;
}

UPawnCameraComponent* AMyCharacter::GetCameraComponent()
{
	return _cameraComponent;
}

UAttributeComponent* AMyCharacter::GetAttributeComponent()
{
	return _attributeComponent;
}

UWeaponComponent* AMyCharacter::GetWeaponComponent() 
{
	return _weaponComponent;
}
AWeapon* AMyCharacter::GetEquippedWeapon()
{
	return _weaponComponent->GetEquipedWeapon();
}
FName AMyCharacter::GetMeshSocketNameByType(EMeshSocketType meshSocketType) 
{
	if (_socketsMap.Contains(meshSocketType))
	{
		return _socketsMap[meshSocketType];
	}
	else
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMeshSocketType"), true);
		if (EnumPtr)
		{
			FString enumName = EnumPtr->GetNameStringByIndex((int32)meshSocketType);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Not registered MeshSocket: " + enumName));
		}
		return "";
	}
}

bool AMyCharacter::GetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform)
{
	if (_socketsMap.Contains(meshSocketType)) 
	{
		outTransform = GetMesh()->GetSocketTransform(_socketsMap[meshSocketType]);
		return true;
	}
	else
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMeshSocketType"), true);
		if (EnumPtr) 
		{
			FString enumName = EnumPtr->GetNameStringByIndex((int32)meshSocketType);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Not registered MeshSocket: " + enumName));
		}
		return false;
	}
}

