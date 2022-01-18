// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandlerComponent.h"
#include "Input/CharacterInputHandler.h"

// Sets default values for this component's properties
UInputHandlerComponent::UInputHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	FName arrButtonNames[] =
	{
		InputActionName::FIRE,
		InputActionName::AIM,
		InputActionName::SPRINT,
		InputActionName::JUMP,
		InputActionName::DODGE,
		InputActionName::Action1,
		InputActionName::Action2,
		InputActionName::Action3,
		InputActionName::Action4,
	};
	_buttonInputActionNames.Append(arrButtonNames, UE_ARRAY_COUNT(arrButtonNames));
}


// Called when the game starts
void UInputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(_inputHandlerClass)
	{
		_inputHandler = NewObject<UCharacterInputHandler>(this, _inputHandlerClass);
		_inputHandler->Initialize();
	}
}


// Called every frame
void UInputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInputHandlerComponent::BindInputs(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &UInputHandlerComponent::HandleAxisInput<EInputType::EIT_Forward>);
	PlayerInputComponent->BindAxis("MoveRight", this, &UInputHandlerComponent::HandleAxisInput<EInputType::EIT_Right>);
	PlayerInputComponent->BindAxis("CameraYaw", this, &UInputHandlerComponent::HandleAxisInput<EInputType::EIT_CameraYaw>);
	PlayerInputComponent->BindAxis("CameraPitch", this, &UInputHandlerComponent::HandleAxisInput<EInputType::EIT_CameraPitch>);
	PlayerInputComponent->BindAxis("CameraZoomInOut", this, &UInputHandlerComponent::HandleAxisInput<EInputType::EIT_CameraZoomInOut>);


	for(FName inputName : _buttonInputActionNames)
	{
		PlayerInputComponent->BindAction<FButtonSignarue>(inputName,IE_Pressed, this, &UInputHandlerComponent::HandleButtonPress, inputName);
		PlayerInputComponent->BindAction<FButtonSignarue>(inputName, IE_Released, this, &UInputHandlerComponent::HandleButtonRelease, inputName);
	}
}

void UInputHandlerComponent::HandleButtonPress(FName actionName)
{
	if (_inputHandler)
	{
		_inputHandler->HandleButtonPress(actionName);
	}
}

void UInputHandlerComponent::HandleButtonRelease(FName actionName)
{
	if (_inputHandler)
	{
		_inputHandler->HandleButtonRelease(actionName);
	}
}

void UInputHandlerComponent::OnCharacterStateChanged(ECharacterState characterState)
{

}

