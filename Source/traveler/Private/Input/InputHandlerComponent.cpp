// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandlerComponent.h"
#include "Input/InputPresetBase.h"

// Sets default values for this component's properties
UInputHandlerComponent::UInputHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UInputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(_inputPresetIns)
	{
		_inputPresetIns->VTick(DeltaTime);
	}
}

void UInputHandlerComponent::BindInputs(UInputComponent* PlayerInputComponent)
{
	_inputPresetIns = _inputPresetClass ? NewObject<UInputPresetBase>(this, _inputPresetClass) : NewObject<UInputPresetBase>(this);
	_inputPresetIns->VInit(GetOwner());

	//Register Axis Inputs
	RegisterAxisInput<NSInputBindingName::MoveForward>(PlayerInputComponent);
	RegisterAxisInput<NSInputBindingName::MoveRight>(PlayerInputComponent);
	RegisterAxisInput<NSInputBindingName::MoveUpward>(PlayerInputComponent);
	RegisterAxisInput<NSInputBindingName::CameraYaw>(PlayerInputComponent);
	RegisterAxisInput<NSInputBindingName::CameraPitch>(PlayerInputComponent);
	RegisterAxisInput<NSInputBindingName::CameraZoomInOut>(PlayerInputComponent);

	//bind Button inputs	
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::Dodge);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::Sprint);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::Jump);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::Fire);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::Aim);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::WeaponControlA);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::WeaponControlB);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::WeaponControlC);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::WeaponControlD);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::WeaponControlE);
	RegisterButtonInput(PlayerInputComponent,NSInputBindingName::WeaponControlF);
}

void UInputHandlerComponent::HandleButtonPressed(FName inputName)
{
	if (_inputPresetIns)
	{
		_inputPresetIns->HandleButtonPressed(inputName);
	}
}

void UInputHandlerComponent::HandleButtonReleased(FName inputName)
{
	if (_inputPresetIns)
	{
		_inputPresetIns->HandleButtonReleased(inputName);
	}
}

void UInputHandlerComponent::RegisterButtonInput(UInputComponent* PlayerInputComponent, FName InputBindingName)
{
	PlayerInputComponent->BindAction<FButtonNameSignarue>(InputBindingName, IE_Pressed, this, &UInputHandlerComponent::HandleButtonPressed, InputBindingName);
	PlayerInputComponent->BindAction<FButtonNameSignarue>(InputBindingName, IE_Released, this, &UInputHandlerComponent::HandleButtonReleased, InputBindingName);
}







