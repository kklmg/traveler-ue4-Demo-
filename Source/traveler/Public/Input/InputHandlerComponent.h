// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputHandlerComponent.generated.h"

DECLARE_DELEGATE_OneParam(FButtonNameSignarue, FName);

class UInputPresetBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRAVELER_API UInputHandlerComponent : public UActorComponent
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

protected:	
	void HandleButtonPressed(FName InputBindingName);
	void HandleButtonReleased(FName InputBindingName);
	template<const FName& bindingName>
	void HandleAxisInput(float value);

	void RegisterButtonInput(UInputComponent* PlayerInputComponent, FName InputBindingName);
	template<const FName& bindingName>
	void RegisterAxisInput(UInputComponent* PlayerInputComponent);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInputPresetBase> _inputPresetClass;

	UPROPERTY()
	UInputPresetBase* _inputPresetIns;
};


template<const FName& bindingName>
void UInputHandlerComponent::HandleAxisInput(float value)
{
	if (_inputPresetIns)
	{
		_inputPresetIns->HandleAxis(bindingName,value);
	}
}

template<const FName& bindingName>
inline void UInputHandlerComponent::RegisterAxisInput(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(bindingName, this, &UInputHandlerComponent::HandleAxisInput<bindingName>);
}
