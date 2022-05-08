// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/FlyingAbilityData.h"
#include "MyCharacterMovementComponent.generated.h"

class IActionInterface;
class IStatusInterface;
class IEventBrokerInterface;

class UAnimationModelBase;
class UActionComponent;
class UStatusComponent;
class UEventBrokerComponent;
class UDataUInt8;
class UDataVector;

/**
 * 
 */
UCLASS()
class TRAVELER_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UMyCharacterMovementComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FFlyingAbilityData& getFlyingAbilityData();
	float ComputeRequiredTimeToBrake();
	float ComputeBrakingDistance();
	float ComputeDistTraveledDuringPitch0();
	void Accelerate(bool bPositive, float deltaTime);
	void RotateYaw(bool bPositive, float deltaTime, float scale = 1.0f);
	void RotateToYaw(float destYaw, float deltaTime);
	void Ascend(bool bPositive, float deltaTime);
	void KeepHorizontal(float deltaTime);
	void KeepSpeed(float normalizedSpeed, float deltaTime);
	void ToggleSprint(bool bSprint);
protected:
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	void PublishEvent_MovementModeChanged();
	void PublishEvent_VelocityModeChanged();

private:
	UPROPERTY(EditDefaultsOnly, Category = FlyingAbility)
	FFlyingAbilityData _FlyingAbilityData;

	//UPROPERTY()
	//UAnimationModelBase* _animationViewModel;

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY()
	UStatusComponent* _statusComp;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;

	UPROPERTY()
	UDataUInt8* _eventData_MovementModeChanged;

	UPROPERTY()
	UDataVector* _eventData_VelocityChanged;

	float _inputDeltaPitch;
	float _inputDeltaYaw;
	bool _bToggleSprint;
};
