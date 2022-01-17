// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Input/InputHandlerInterface.h"
#include "Data/EnumCharacterState.h"
#include "Data/EnumInputType.h"
#include "InputHandlerComponent.generated.h"

DECLARE_DELEGATE_OneParam(FButtonSignarue,EInputType);

class UCharacterInputHandler;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	void HandleButtonPress(EInputType inputType);
	void HandleButtonRelease(EInputType inputType);

	virtual void VGoForward() override;
	virtual void VGoRight() override;

	virtual void VCameraPitch() override;
	virtual void VCameraYaw() override;
	virtual void VCameraZoomInOut() override;

	virtual void VPressButtonJump() override;
	virtual void VReleaseButtonJump() override;

	virtual void VPressButtonSprint() override;
	virtual void VReleaseButtonSprint() override;

	virtual void VPressButtonDodge() override;
	virtual void VReleaseButtonDodge() override;

	virtual void VPressButtonFire() override;
	virtual void VReleaseButtonFire() override;

	virtual void VPressButtonAim() override;
	virtual void VReleaseButtonAim() override;

	virtual void VPressButtonAction1() override;
	virtual void VReleaseButtonAction1() override;

	virtual void VPressButtonAction2() override;
	virtual void VReleaseButtonAction2() override;

	virtual void VPressButtonAction3() override;
	virtual void VReleaseButtonAction3() override;

	virtual void VPressButtonAction4();
	virtual void VReleaseButtonAction4();

public:
	UFUNCTION()
	void OnCharacterStateChanged(ECharacterState characterState);

private:
	TMap<ECharacterState,TSubclassOf<UCharacterInputHandler>> _mapInputHandlerClasses;

	UPROPERTY()
	UCharacterInputHandler* _inputHandler;
};
