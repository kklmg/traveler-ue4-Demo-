// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/PawnCameraComponent.h"
#include "CharacterCameraInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterCameraInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API ICharacterCameraInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void VCameraArmPitch(float angle) PURE_VIRTUAL(ICharacterCameraInterface::VCameraArmPitch,);
	UFUNCTION()
	virtual void VCameraArmYaw(float angle)  PURE_VIRTUAL(ICharacterCameraInterface::VCameraArmYaw, );
	UFUNCTION()
	virtual void VCameraZoomInOut(float offset) PURE_VIRTUAL(ICharacterCameraInterface::VCameraZoomInOut, );
	UFUNCTION()
	virtual FRotator VGetCameraRotation() PURE_VIRTUAL(ICharacterCameraInterface::VGetCameraRotation, return FRotator(););
	UFUNCTION()
	virtual FVector VGetCameraLocation() PURE_VIRTUAL(ICharacterCameraInterface::VGetCameraLocation, return FVector(););
	UFUNCTION()
	virtual void VDragCamera(FVector offset) PURE_VIRTUAL(ICharacterCameraInterface::DragCamera,);
	UFUNCTION()
	virtual void VCancelDragCamera() PURE_VIRTUAL(ICharacterCameraInterface::CancelDragCamera,);
	UFUNCTION()
	virtual void VSetCameraArmPitchLimit(float pitchMin, float pitchMax) PURE_VIRTUAL(ICharacterCameraInterface::VSetCameraArmPitchLimit, );
	UFUNCTION()
	virtual void VResetCameraArmPitchLimit() PURE_VIRTUAL(ICharacterCameraInterface::VResetCameraArmPitchLimit, );
	UFUNCTION()
	virtual float VGetCameraArmLength() PURE_VIRTUAL(ICharacterCameraInterface::VGetCameraArmLength, return 0.0f; );
	UFUNCTION()
	virtual UCameraComponent* VGetCameraComponent()  PURE_VIRTUAL(ICharacterCameraInterface::VGetCameraComponent,return nullptr; );
};
