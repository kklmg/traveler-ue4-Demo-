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

/**
 * 
 */
UCLASS()
class TRAVELER_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UMyCharacterMovementComponent();

	FFlyingAbilityData& getFlyingAbilityData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	void PublishMovementModeChangedEvent();

	UFUNCTION()
	void OnCharacterWantToSprint(bool wantToSprint);

private:
	UPROPERTY(EditDefaultsOnly, Category = FlyingAbility)
	FFlyingAbilityData _FlyingAbilityData;

	UPROPERTY()
	UAnimationModelBase* _animationViewModel;

	IActionInterface* _actionInterface;
	IStatusInterface* _statusInterface;
	IEventBrokerInterface* _eventBrokerInterface;
};
