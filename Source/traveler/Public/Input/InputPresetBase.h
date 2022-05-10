// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Input/InputBindingNames.h"
#include "InputPresetBase.generated.h"

class UAxisInputBase;
class UButtonInputBase;
class UWeaponComponent;
class UEventBrokerComponent;
class UActionComponent;
class ICharacterCameraInterface;

/**
 * 
 */


UCLASS(BlueprintType,Blueprintable)
class TRAVELER_API UInputPresetBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void VInit(AActor* owner);
	virtual void VTick(float deltaTime);

	void HandleAxis(FName inputBindingName,float value);
	void HandleButtonPressed(FName inputBindingName);
	void HandleButtonReleased(FName inputBindingName);

	UActionComponent* GetActionComp();
	UWeaponComponent* GetWeaponComp();
	UEventBrokerComponent* GetEventBrokerComp();
	ICharacterCameraInterface* GetCameraInterface();

protected:
	void RegisterAxisInput(UAxisInputBase* axisInput);
	void RegisterButtonInput(UButtonInputBase* buttonInput);

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UButtonInputBase>> _presetButtonClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UButtonInputBase>> _presetAxisClass;

	UPROPERTY()
	TMap<FName, UButtonInputBase*> _mapButtonIns;

	UPROPERTY()
	TMap<FName, UAxisInputBase*> _mapAxisIns;

	UPROPERTY()
	AActor* _owner;

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY()
	UWeaponComponent* _weaponComp;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;

	ICharacterCameraInterface* _cameraInterface;
};
//
//
//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//void BindInputs(UInputComponent* PlayerInputComponent);
//
//void HandleButtonPress(FName inputName);
//void HandleButtonRelease(FName inputName);
//
//UFUNCTION()
//void ReceiveInputMoveX(float value);
//UFUNCTION()
//void ReceiveInputMoveY(float value);
//UFUNCTION()
//void ReceiveInputMoveZ(float value);
//UFUNCTION()
//void ReceiveInputCameraArmYaw(float value);
//UFUNCTION()
//void ReceiveInputCameraArmPitch(float value);
//UFUNCTION()
//void ReceiveInputCameraZoomInOut(float value);
//
//protected:
//	void HandleButtonsPressing(float deltaTime);
//	void ConsumeMovementInput();
//	void InitializeButtons();
//
//private:
//	UPROPERTY(EditDefaultsOnly)
//		TArray<TSubclassOf<UButtonInputActionBase>> _presetButtons;
//
//	UPROPERTY()
//		TMap<FName, UButtonInputActionBase*> _mapButtons;
//
//	UPROPERTY()
//		UActionComponent* _actionComp;
//
//	ICharacterCameraInterface* _cameraInterface;
//	FVector _movementInput;


//
//PlayerInputComponent->BindAxis("MoveForward", this, &UInputHandlerComponent::ReceiveInputMoveX);
//PlayerInputComponent->BindAxis("MoveRight", this, &UInputHandlerComponent::ReceiveInputMoveY);
//
//PlayerInputComponent->BindAxis("CameraYaw", this, &UInputHandlerComponent::ReceiveInputCameraArmYaw);
//PlayerInputComponent->BindAxis("CameraPitch", this, &UInputHandlerComponent::ReceiveInputCameraArmPitch);
//PlayerInputComponent->BindAxis("CameraZoomInOut", this, &UInputHandlerComponent::ReceiveInputCameraZoomInOut);
