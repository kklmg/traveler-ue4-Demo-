// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/PlayerInputPresetBase.h"
#include "Components/ActionComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Components/EventBrokerComponent.h"
#include "Interface/CharacterCameraInterface.h"
#include "Input/AxisInputDelegate.h"



void UPlayerInputPresetBase::VInit(AActor* owner)
{
	Super::VInit(owner);

	RegisterAxisInput(UAxisInputDelegate::MakeInstance(this, NSInputBindingName::MoveForward, this, &UPlayerInputPresetBase::Axis_MoveForward));
	RegisterAxisInput(UAxisInputDelegate::MakeInstance(this, NSInputBindingName::MoveRight, this, &UPlayerInputPresetBase::Axis_MoveRight));
	RegisterAxisInput(UAxisInputDelegate::MakeInstance(this, NSInputBindingName::MoveUpward, this, &UPlayerInputPresetBase::Axis_MoveUpward));
	RegisterAxisInput(UAxisInputDelegate::MakeInstance(this, NSInputBindingName::CameraYaw, this, &UPlayerInputPresetBase::Axis_CameraArmYaw));
	RegisterAxisInput(UAxisInputDelegate::MakeInstance(this, NSInputBindingName::CameraPitch, this, &UPlayerInputPresetBase::Axis_CameraArmPitch));
	RegisterAxisInput(UAxisInputDelegate::MakeInstance(this, NSInputBindingName::CameraZoomInOut, this, &UPlayerInputPresetBase::Axis_CameraZoomInOut));
}

void UPlayerInputPresetBase::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

	ConsumeMovementInput();
}

void UPlayerInputPresetBase::ConsumeMovementInput()
{
	if (_movementInput.IsZero()) return;
	if (!GetActionComp()) return;

	if (GetCameraInterface())
	{
		//Get Moving Direction 
		FVector movingDir = GetCameraInterface()->VGetCameraRotation().RotateVector(_movementInput);
		movingDir.Z = 0;

		//Execute Moving Action
		GetActionComp()->GetActionBlackBoard()->WriteData_FVector(EActionDataKey::EACTD_MovementInput, movingDir);
		GetActionComp()->ExecuteAction(EActionType::EACT_Moving);
	}
}

void UPlayerInputPresetBase::Axis_MoveForward(float value)
{
	_movementInput.X = value;
}

void UPlayerInputPresetBase::Axis_MoveRight(float value)
{
	_movementInput.Y = value;
}

void UPlayerInputPresetBase::Axis_MoveUpward(float value)
{
	_movementInput.Z = value;
}

void UPlayerInputPresetBase::Axis_CameraArmYaw(float value)
{
	if (GetCameraInterface())
	{
		GetCameraInterface()->VCameraArmYaw(value);
	}
}

void UPlayerInputPresetBase::Axis_CameraArmPitch(float value)
{
	if (GetCameraInterface())
	{
		GetCameraInterface()->VCameraArmPitch(value);
	}
}

void UPlayerInputPresetBase::Axis_CameraZoomInOut(float value)
{
	if (GetCameraInterface())
	{
		GetCameraInterface()->VCameraZoomInOut(value);
	}
}
