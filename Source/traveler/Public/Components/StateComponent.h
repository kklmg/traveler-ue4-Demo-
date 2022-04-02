// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/StateInterface.h"
#include "StateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UStateComponent : public UActorComponent, public IStateInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//FStateData VGetStateData() override;

	//void VSetSituationState(ESituationState newState) override;
	//void VSetHealthState(EHealthState newState) override;
	//void VSetPostureState(EPostureState newState) override;

	//FOnSituationStateChanged* VGetSituationStateChangedDelegate() override;
	//FOnHealthStateChanged* VGetHealthStateChangedDelegate() override;
	//FOnPostureStateChanged* VGetPostureStateChangedDelegate() override;
	//FOnAnyStateChanged* VGetAnyStateChangedDelegate() override;

	//UFUNCTION()
	//void OnCharacterMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

private:
	UPROPERTY(EditDefaultsOnly)
	FStateData _stateData;
	
	FOnSituationStateChanged _situationStateChangedDelegate;
	FOnHealthStateChanged _healthStateChangedDelegate;
	FOnPostureStateChanged _postureStateChangedDelegate;
	FOnAnyStateChanged _anyStateChangedDelegate;
};
