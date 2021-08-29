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
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	//if (!MovementInput.IsZero())
	//{
	//	//Scale our movement input axis values by 100 units per second
	//	MovementInput = MovementInput * 100.0f;
	//	FVector NewLocation = GetActorLocation();
	//	NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
	//	NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
	//	SetActorLocation(NewLocation);
	//}

	//Zoom in if ZoomIn button is down, zoom back out if it's not
	//{
	//	if (bZoomingIn)
	//	{
	//		ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
	//	}
	//	else
	//	{
	//		ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
	//	}
	//}
	//	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	//	//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
	//	_cameraComponent->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	//	_cameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	//}

	////Rotate our actor's yaw, which will turn our camera because we're attached to it
	//{
	//	FRotator NewRotation = GetActorRotation();
	//	NewRotation.Yaw += CameraInput.X;
	//	SetActorRotation(NewRotation);
	//}

	////Rotate our camera's pitch, but limit it so we're always looking downward
	//{
	//	FRotator NewRotation = _cameraSpringArm->GetComponentRotation();
	//	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
	//	_cameraSpringArm->SetWorldRotation(NewRotation);
	//}

	////Handle movement based on our "MoveX" and "MoveY" axes
	//{
	//	if (!MovementInput.IsZero())
	//	{
	//		//Scale our movement input axis values by 100 units per second
	//		MovementInput = MovementInput.SafeNormal() * 100.0f;
	//		FVector NewLocation = GetActorLocation();
	//		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
	//		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
	//		SetActorLocation(NewLocation);
	//	}
	//}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);


	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);

	
	//InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMyCharacter::ZoomIn);
	//InputComponent->BindAction("ZoomIn", IE_Released, this, &AMyCharacter::ZoomOut);

	
	InputComponent->BindAxis("CameraPitch", this, &AMyCharacter::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &AMyCharacter::YawCamera);

	InputComponent->BindAxis("ZoomInOut", this, &AMyCharacter::ZoomInOut);
}

void AMyCharacter::MoveForward(float Value)
{
	
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMyCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
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

