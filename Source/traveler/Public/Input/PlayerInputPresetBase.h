// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputPresetBase.h"
#include "PlayerInputPresetBase.generated.h"


/**
 * 
 */
UCLASS()
class TRAVELER_API UPlayerInputPresetBase : public UInputPresetBase
{
	GENERATED_BODY()
public:
	virtual void VInit(AActor* owner) override;
	virtual void VTick(float deltaTime) override;

protected:
	virtual void ConsumeMovementInput();

	void Axis_MoveForward(float value);
	void Axis_MoveRight(float value);
	void Axis_MoveUpward(float value);
	void Axis_CameraArmYaw(float value);
	void Axis_CameraArmPitch(float value);
	void Axis_CameraZoomInOut(float value);

	void Button_WeaponControlA();
	void Button_WeaponControlB();
	void Button_WeaponControlC();
	void Button_WeaponControlD();
	void Button_WeaponControlE();
	void Button_WeaponControlF();

private:
	FVector _movementInput;
};
