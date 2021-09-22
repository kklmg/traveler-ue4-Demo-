// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


	_cameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	_cameraSpringArm->SetupAttachment(GetCapsuleComponent());
	_cameraSpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	_cameraSpringArm->TargetArmLength = 200.0f;
	//_cameraSpringArm->bEnableCameraLag = true;
	//_cameraSpringArm->CameraLagSpeed = 3.0f;

	// Create a first person camera component.
	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(_cameraComponent != nullptr);

	_cameraComponent->SetupAttachment(_cameraSpringArm, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;

	_stateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("stateComponent"));

	// Attach the camera component to our capsule component.
	//_cameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	//_cameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	//_cameraComponent->bUsePawnControlRotation = true;

	//AutoPossessPlayer = EAutoReceiveInput::Player0;
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

	_pMovementHandler->HandleMovement(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	//jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	//camera
	InputComponent->BindAxis("CameraPitch", this, &AMyCharacter::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &AMyCharacter::YawCamera);
	InputComponent->BindAxis("ZoomInOut", this, &AMyCharacter::ZoomInOut);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMyCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AMyCharacter::CancelAim);
}

void AMyCharacter::MoveForward(float Value)
{
	_pMovementHandler->SetMovementInputX(Value);
	_pMovementHandler->SetCameraRotation(_cameraComponent->GetComponentRotation());


	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, GetVelocity().ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::SanitizeFloat(camreaRotation.Yaw));
}

void AMyCharacter::MoveRight(float Value)
{	
	_pMovementHandler->SetMovementInputY(Value);
	_pMovementHandler->SetCameraRotation(_cameraComponent->GetComponentRotation());

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::SanitizeFloat(camreaRotation.Yaw));
}


void AMyCharacter::StartJump()
{
	bPressedJump = true;
}

void AMyCharacter::StopJump()
{
	bPressedJump = false;
}

UStateComponent* AMyCharacter::GetStateComponent()
{
	return _stateComponent;
}

void AMyCharacter::PitchCamera(float AxisValue)
{
	FRotator rotation = _cameraSpringArm->GetRelativeRotation();
	float pitch = rotation.Pitch + AxisValue;
	rotation.Pitch = pitch > 0 ? FMath::Clamp(rotation.Pitch + AxisValue, 0.0f, 89.9f) : FMath::Clamp(rotation.Pitch + AxisValue, -89.9f, 0.0f);
	
	_cameraSpringArm->SetRelativeRotation(rotation);
}

void AMyCharacter::YawCamera(float AxisValue)
{
	FRotator DeltaRotation(ForceInit);
	DeltaRotation.Yaw = (AxisValue);

	_cameraSpringArm->AddRelativeRotation(DeltaRotation);
}



void AMyCharacter::ZoomInOut(float AxisValue)
{
	_cameraSpringArm->TargetArmLength = FMath::Clamp(_cameraSpringArm->TargetArmLength + AxisValue*_zoomSpeed, 200.0f, 400.0f);

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::SanitizeFloat(_cameraSpringArm->TargetArmLength));
}


void AMyCharacter::Aim()
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

	if (_stateComponent) 
	{
		_stateComponent->equipState = EEquipState::ES_bow;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, " Aim");
	}
}


void AMyCharacter::CancelAim()
{
	if (_stateComponent)
	{
		_stateComponent->equipState = EEquipState::ES_unEquiped;

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Cancel Aim");
	}
}

