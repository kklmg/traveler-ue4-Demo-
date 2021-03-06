// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/EnumProcessState.h"
#include "Enums/EnumActionType.h"
#include "ActionComponent.generated.h"

class UActionBase;
class UActionPresetGroup;
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
	UFUNCTION()
	void OnMovementModeChanged(ACharacter* character, EMovementMode prevMovementMode, uint8 previousCustomMode);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AbortAllActions();
	bool OverrideActionPresetGroup(TSubclassOf<UActionPresetGroup> actionPresetGroupClass);
	void ClearOverridedActionPresetGroup();

public:
	UFUNCTION(BlueprintCallable)
	bool IsActionAlive(EActionType actionType);

	UFUNCTION(BlueprintCallable)
	EProcessState GetActionState(EActionType actionType);

	UFUNCTION(BlueprintCallable)
	void ExecuteAction(EActionType actionType);

	UFUNCTION(BlueprintCallable)
	void AbortAction(EActionType actionType);

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* GetActionBlackBoard();
protected:
	UActionPresetGroup* GetCurActionPresetGroup();

private:
	UPROPERTY()
	ACharacter* _character;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;

	UPROPERTY()
	UActionBlackBoard* _actionBlackBoard;

	UPROPERTY(EditDefaultsOnly, Category = ActionPresetGroup)
	TSubclassOf<UActionPresetGroup> _basicActionPresetGroupClass;

	UPROPERTY()
	UActionPresetGroup* _basicActionPresetGroupIns;

	UPROPERTY()
	UActionPresetGroup* _overridedActionPresetGroupIns;

	bool _bActorAlive;
	bool _bActionPresetGroupOverrided;
};


