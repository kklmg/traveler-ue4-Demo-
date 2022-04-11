// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponent.generated.h"

class IActionInterface;
class IStatusInterface;
class IEventBrokerInterface;

class UAnimationModelBase;

USTRUCT(BlueprintType)
struct FFlygingSimulationData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	float TimeFrame_StartAccelerate;
	UPROPERTY(BlueprintReadWrite)
	float TimeFrame_OnMaxSpeed;
	UPROPERTY(BlueprintReadWrite)
	float TimeFrame_StartDecelerate;
	UPROPERTY(BlueprintReadWrite)
	float TimeFrame_Stop;


	float ElapsedTime;

	bool bIsSimulating;

	void StopSimulation()
	{
		ElapsedTime = 0.0f;
		bIsSimulating = false;
	}

	void ShowDebugMessage()
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "TimeFrame_StartAccelerate: " + FString::SanitizeFloat(TimeFrame_StartAccelerate));
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "TimeFrame_OnMaxSpeed: " + FString::SanitizeFloat(TimeFrame_OnMaxSpeed));
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "TimeFrame_StartDecelerate: " + FString::SanitizeFloat(TimeFrame_StartDecelerate));
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Black, "TimeFrame_Stop: " + FString::SanitizeFloat(TimeFrame_Stop));
	}
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UMyCharacterMovementComponent();

	FFlygingSimulationData GenerateFlyingUpSimulationData(float targetAltitude);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	void PublishMovementModeChangedEvent();

	UFUNCTION()
	void OnCharacterWantToSprint(bool wantToSprint);

	void StartSimulationFlyingUp(float targetAltitude);
	void SimulationTick(float deltaTime);

private:

	FFlygingSimulationData _simulationData;

	UPROPERTY(EditDefaultsOnly, Category = Flying)
	bool _bUpdateDestination;

	UPROPERTY(EditDefaultsOnly, Category = Flying)
	float _rollLimit;
	UPROPERTY(EditDefaultsOnly, Category = Flying)
	float _rollRate;
	UPROPERTY(EditDefaultsOnly, Category = Flying)
	float _pitchLimit;
	UPROPERTY(EditDefaultsOnly, Category = Flying)
	float _pitchRate;
	UPROPERTY(EditDefaultsOnly, Category = Flying)
	float _yawRate;

	float _preRoll;

	float _resetFactor;
	float _resetFactorSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Flying)
	UAnimationModelBase* _animationViewModel;

	IActionInterface* _actionInterface;
	IStatusInterface* _statusInterface;
	IEventBrokerInterface* _eventBrokerInterface;
};
