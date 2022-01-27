// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Input/InputHandlerInterface.h"
#include "Data/EnumCharacterState.h"
#include "Data/EnumInputType.h"
#include "InputHandlerComponent.generated.h"


DECLARE_DELEGATE_OneParam(FButtonSignature, bool);
DECLARE_DELEGATE_OneParam(FButtonNameSignarue, FName);

class UButtonInputActionBase;


class IActionInterface;
class ICharacterCameraInterface;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRAVELER_API UInputHandlerComponent : public UActorComponent, public IInputHandlerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void BindInputs(UInputComponent* PlayerInputComponent);

	void HandleButtonPress(FName inputName);
	void HandleButtonRelease(FName inputName);

	UFUNCTION()
	void ReceiveInputMoveX(float value);
	UFUNCTION()
	void ReceiveInputMoveY(float value);
	UFUNCTION()
	void ReceiveInputMoveZ(float value);
	UFUNCTION()
	void ReceiveInputCameraArmYaw(float value);
	UFUNCTION()
	void ReceiveInputCameraArmPitch(float value);
	UFUNCTION()
	void ReceiveInputCameraZoomInOut(float value);

//	UFUNCTION()
//		void OnAction1ButtonDown();
//	UFUNCTION()
//		void OnAction1ButtonUp();
//	UFUNCTION()
//		void OnAction2ButtonDown();
//	UFUNCTION()
//		void OnAction2ButtonUp();
//	UFUNCTION()
//		void OnAction3ButtonDown();
//	UFUNCTION()
//		void OnAction3ButtonUp();
//
//TArray<FButtonSignature> _buttonSignatures;
//
//	FButtonSignature Action1ButtonDownDelegate;
//	FButtonSignature Action2ButtonDownDelegate;
//	FButtonSignature Action3ButtonDownUpDelegate;
//	FButtonSignature Action4ButtonDownUpDelegate;
//
//	FButtonSignature Action1ButtonUpDelegate;
//	FButtonSignature Action2ButtonUpDelegate;
//	FButtonSignature Action3ButtonDownUpDelegate;
//	FButtonSignature Action4ButtonDownUpDelegate;


	void ConsumeMovementInput();

	void InitializeButtons();

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UButtonInputActionBase>> _presetButtons;

	UPROPERTY()
	TMap<FName,UButtonInputActionBase*> _mapButtons;

	IActionInterface* _actionInterface;
	ICharacterCameraInterface* _cameraInterface;

	FVector _movementInput;
};
