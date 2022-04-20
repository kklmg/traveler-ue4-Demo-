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

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY()
	UStatusComponent* _statusComp;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;
};
