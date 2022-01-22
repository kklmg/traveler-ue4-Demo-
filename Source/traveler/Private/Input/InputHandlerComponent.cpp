// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandlerComponent.h"
#include "Input/ButtonInputActionBase.h"
#include "Interface/ActionInterface.h"
#include "Interface/CharacterCameraInterface.h"

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

	_actionInterface = GetOwner<IActionInterface>();
	if(!_actionInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("get actionInterface failed!"));
	}

	_cameraInterface = GetOwner<ICharacterCameraInterface>();
	if (!_cameraInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("get CharacterCameraInterface failed!"));
	}

	InitializeButtons();
}


// Called every frame
void UInputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	ConsumeMovementInput();
}

void UInputHandlerComponent::BindInputs(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &UInputHandlerComponent::ReceiveInputMoveX);
	PlayerInputComponent->BindAxis("MoveRight", this, &UInputHandlerComponent::ReceiveInputMoveY);

	PlayerInputComponent->BindAxis("CameraYaw", this, &UInputHandlerComponent::ReceiveInputCameraArmYaw);
	PlayerInputComponent->BindAxis("CameraPitch", this, &UInputHandlerComponent::ReceiveInputCameraArmPitch);
	PlayerInputComponent->BindAxis("CameraZoomInOut", this, &UInputHandlerComponent::ReceiveInputCameraZoomInOut);

	for (TSubclassOf<UButtonInputActionBase> buttonClass : _presetButtons)
	{
		if (buttonClass == nullptr)continue;
		FName inputName = buttonClass.GetDefaultObject()->GetInputMappingName();
		PlayerInputComponent->BindAction<FButtonSignarue>(inputName, IE_Pressed, this, &UInputHandlerComponent::HandleButtonPress, inputName);
		PlayerInputComponent->BindAction<FButtonSignarue>(inputName, IE_Released, this, &UInputHandlerComponent::HandleButtonRelease, inputName);
	}
}

void UInputHandlerComponent::HandleButtonPress(FName inputName)
{
	if (_mapButtons.Contains(inputName))
	{
		_mapButtons[inputName]->VPress();
	}
}

void UInputHandlerComponent::HandleButtonRelease(FName inputName)
{
	if (_mapButtons.Contains(inputName))
	{
		_mapButtons[inputName]->VRelease();
	}
}

void UInputHandlerComponent::ReceiveInputMoveX(float value)
{
	_movementInput.X = value;
}

void UInputHandlerComponent::ReceiveInputMoveY(float value)
{
	_movementInput.Y = value;
}

void UInputHandlerComponent::ReceiveInputMoveZ(float value)
{
	_movementInput.Z = value;
}

void UInputHandlerComponent::ReceiveInputCameraArmYaw(float value)
{
	if (_cameraInterface)
	{
		_cameraInterface->VCameraArmYaw(value);
	}
}

void UInputHandlerComponent::ReceiveInputCameraArmPitch(float value)
{
	if (_cameraInterface)
	{
		_cameraInterface->VCameraArmPitch(value);
	}
}

void UInputHandlerComponent::ReceiveInputCameraZoomInOut(float value)
{
	if (_cameraInterface)
	{
		_cameraInterface->VCameraZoomInOut(value);
	}
}


void UInputHandlerComponent::ConsumeMovementInput()
{
	if(!_movementInput.IsZero() && _actionInterface && _cameraInterface)
	{
		//map input direction to camera direction
		FRotator cameraRotator = _cameraInterface->VGetCameraRotation();
		FVector movement = cameraRotator.RotateVector(_movementInput);
		movement.Z = 0;

		_actionInterface->VGetActionBlackBoard()->WriteData_FVector(EActionData::EACTD_MovementInput, movement);
		_actionInterface->VExecuteAction(EActionType::EACT_Moving);

		_movementInput = FVector::ZeroVector;
	}
}

void UInputHandlerComponent::InitializeButtons()
{
	for (TSubclassOf<UButtonInputActionBase> buttonClass : _presetButtons)
	{
		if (buttonClass == nullptr)continue;
		if(_mapButtons.Contains(buttonClass.GetDefaultObject()->GetInputMappingName()))
		{
			UE_LOG(LogTemp,Warning,TEXT("Existing duplicate button input class"))
		}
		else
		{
			UButtonInputActionBase* buttonIns = NewObject<UButtonInputActionBase>(this, buttonClass);
			buttonIns->Initialize(_actionInterface);
			_mapButtons.Add(buttonIns->GetInputMappingName(),buttonIns);
		}
	}
}





