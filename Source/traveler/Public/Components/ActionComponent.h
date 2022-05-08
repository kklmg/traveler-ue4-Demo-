// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

class UActionBase;
class UActionPreset;
class UCharacterActionPreset;
class UActionBlackBoard;
class UEventBrokerComponent;
class ACharacter;


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

	void OnReceiveEvent_LifeStateChanged(UObject* baseData);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AbortAllActions();
	bool IsActionRunning(EActionType actionType);
	void SwitchActionSet(UActionPreset* actionSet);

public:
	UFUNCTION(BlueprintCallable)
	UActionBase* ExecuteAction(EActionType actionType);

	UFUNCTION(BlueprintCallable)
	UActionBase* AbortAction(EActionType actionType);

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* GetActionBlackBoard();

private:

	UPROPERTY()
	ACharacter* _character;

	UPROPERTY()
	UActionBlackBoard* _actionBlackBoard;

	UPROPERTY(EditDefaultsOnly, Category = ActionSetTriggerClasses)
	TArray<TSubclassOf<UActionPreset>> _actionPresetClasses;

	UPROPERTY()
	TArray<UActionPreset*> _actionPresetInstances;

	UPROPERTY()
	UActionPreset* _curActionSet;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;

	bool _bActorAlive;
};


