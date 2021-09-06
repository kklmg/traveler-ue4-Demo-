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
}

void AMyCharacter::MoveForward(float Value)
{
	_pMovementHandler->SetMovementInputX(Value);
	_pMovementHandler->SetCameraRotation(_cameraComponent->GetComponentRotation());

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

