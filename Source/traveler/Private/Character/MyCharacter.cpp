// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CameraSpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/MovementHandler.h"
#include "Components/WeaponComponent.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "Components/AttributeComponent.h"
#include "Projectile/Projectile.h"


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
	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(_cameraComponent != nullptr);
	_cameraComponent->SetupAttachment(_cameraSpringArmComponent, USpringArmComponent::SocketName);

	//Create state component
	_stateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("stateComponent"));
	check(_stateComponent != nullptr);

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
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character BeginPlay"));

	_pMovementHandler = new MovementHandler(this);
}

void AMyCharacter::BeginDestroy()
{
	Super::BeginDestroy();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character BeginPlay"));

	if (_pMovementHandler != nullptr) 
	{
		delete(_pMovementHandler);
		_pMovementHandler = nullptr;
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//_pMovementHandler->HandleMovement(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//movement
	PlayerInputComponent->BindAxis("MoveForward", _actionComponent, &UActionComponent::AddMovementInputX);
	PlayerInputComponent->BindAxis("MoveRight", _actionComponent, &UActionComponent::AddMovementInputY);
	//PlayerInputComponent->bindax

	//jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	//camera
	InputComponent->BindAxis("CameraPitch", _cameraSpringArmComponent, &UCameraSpringArmComponent::Pitch);
	InputComponent->BindAxis("CameraYaw", _cameraSpringArmComponent, &UCameraSpringArmComponent::Yaw);
	InputComponent->BindAxis("ZoomInOut", _cameraSpringArmComponent, &UCameraSpringArmComponent::ZoomInOut);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMyCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AMyCharacter::CancelAim);
}

void AMyCharacter::MoveForward(float Value)
{
	_pMovementHandler->SetMovementInputX(Value);
	_pMovementHandler->SetCameraRotation(_cameraComponent->GetComponentRotation());

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, GetVelocity().ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::SanitizeFloat(camreaRotation.Yaw));

	//_actionComponent->Move();
}

void AMyCharacter::MoveRight(float Value)
{	
	_pMovementHandler->SetMovementInputY(Value);
	_pMovementHandler->SetCameraRotation(_cameraComponent->GetComponentRotation());

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::SanitizeFloat(camreaRotation.Yaw));

	//_actionComponent->Move();
}


void AMyCharacter::StartJump()
{
	_actionComponent->Jump();

	//bPressedJump = true;
}

void AMyCharacter::StopJump()
{
	_actionComponent->Jump();

	bPressedJump = false;
}

UStateComponent* AMyCharacter::GetStateComponent()
{
	return _stateComponent;
}

void AMyCharacter::Aim()
{
	if (_stateComponent) 
	{
		_stateComponent->equipState = EEquipState::ES_bow;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, " Aim");
	}

	if (_cameraComponent) 
	{
		//_cameraComponent->AddLocalOffset(FVector(10, 10, 10));
		//_cameraSpringArm->AddLocalOffset(FVector(10, 10, 10));
	}
	if (_actionComponent) 
	{
		_actionComponent->Target();
	}

}


void AMyCharacter::CancelAim()
{
	LaunchProjectile();

	if (_stateComponent)
	{
		_stateComponent->equipState = EEquipState::ES_unEquiped;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Cancel Aim");
	}
	if (_actionComponent)
	{
		_actionComponent->Target();
	}
}

void AMyCharacter::LaunchProjectile() 
{
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}

	if (_actionComponent)
	{
		//_actionComponent->();
	}
}

UCameraSpringArmComponent* AMyCharacter::GetSpringArmComponent()
{
	return _cameraSpringArmComponent;
}

UCameraComponent* AMyCharacter::GetCameraComponent()
{
	return _cameraComponent;
}

UAttributeComponent* AMyCharacter::GetAttributeComponent()
{
	return _attributeComponent;
}

