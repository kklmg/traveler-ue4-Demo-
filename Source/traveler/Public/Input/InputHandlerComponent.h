// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Input/InputHandlerInterface.h"
#include "Data/EnumCharacterState.h"
#include "Data/EnumInputType.h"
#include "InputHandlerComponent.generated.h"


DECLARE_DELEGATE_OneParam(FButtonSignarue, FName);

class UCharacterInputHandler;

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

	template<EInputType type> void HandleAxisInput(float value);
	void HandleButtonPress(FName actionName);
	void HandleButtonRelease(FName actionName);

public:
	UFUNCTION()
	void OnCharacterStateChanged(ECharacterState characterState);

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FName> _axisInputActionNames;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> _buttonInputActionNames;

	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterState,TSubclassOf<UCharacterInputHandler>> _mapInputHandlerClasses;

	UPROPERTY()
	TSubclassOf<UCharacterInputHandler> _inputHandlerClass;

	UPROPERTY()
	UCharacterInputHandler* _inputHandler;
};


template<EInputType type> void UInputHandlerComponent::HandleAxisInput(float value)
{
	if (_inputHandler)
	{
		_inputHandler->HandleAxisInput(type, value);
	}
}