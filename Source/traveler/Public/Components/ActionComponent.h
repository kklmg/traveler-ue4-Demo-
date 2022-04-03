// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/StateData.h"
#include "ActionComponent.generated.h"

class UActionBase;
class UCharacterActionPreset;
class UActionBlackBoard;
class IEventBrokerInterface;
class UActionPresetTrigger;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ClearActionProcessPool();

	bool CheckActionIsInProgress(EActionType actionType);

	UFUNCTION()
	void OnCharacterStateChanged(FStateData newStateData);

	void SwitchActionSet(UCharacterActionPreset* actionSet);

public:
	UFUNCTION(BlueprintCallable)
	UActionBase* ExecuteAction(EActionType actionType);

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* GetActionBlackBoard();

	IEventBrokerInterface* GetEventBrokerInterface();
	
private:
	void _TickActionProcess(float deltaTime);

private:
	FVector _userMovementInput;

	FStateData _cachedStateData;

	//UPROPERTY()
	//TMap<EActionType, UActionBase*> _mapActionProcessPool;

	UPROPERTY()
	TArray<UActionBase*> _mapActionProcessPool;

	UPROPERTY()
	UActionBlackBoard* _actionBlackBoard;

	UPROPERTY(EditDefaultsOnly, Category = ActionSetClasses)
	TMap<TEnumAsByte<enum EMovementMode>, TSubclassOf<UCharacterActionPreset>> _mapActionPreset;

	UPROPERTY(EditDefaultsOnly, Category = ActionSetClasses)
	TArray<UActionPresetTrigger*> _actionSetTriggers;


	UPROPERTY()
	UCharacterActionPreset* _curActionSet;

	IEventBrokerInterface* _eventBrokerInterface;

	bool _bSprintButtonPress;
};
