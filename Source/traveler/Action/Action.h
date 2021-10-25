// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Process.h"
#include "Action.generated.h"

UENUM(BlueprintType)
enum class EActionState : uint8
{
	AS_UNINITIALIZED UMETA(DisplayName = "UNINITIALIZED"),
	// Living processes
	AS_RUNNING UMETA(DisplayName = "RUNNING"),  // initialized and running
	AS_PAUSED UMETA(DisplayName = "PAUSED"),  // initialized but paused

	// Dead processes
	//AS_SUCCEEDED UMETA(DisplayName = "SUCCEEDED"),  // completed successfully
	//AS_FAILED UMETA(DisplayName = "FAILED"),  // failed to complete
	AS_FINISHED UMETA(DisplayName = "FINISHED"),
};

/**
 *
 */
UCLASS()
class TRAVELER_API UAction : public UObject
{
	GENERATED_BODY()
public:
	void Start();

	void Pause();
	void Stop();

	bool CanStart();
	EActionState GetState() const;
	void SetState(EActionState state);

public:
	virtual void VInitialize();
	virtual void VUpdate(unsigned long deltaMs);

public:
	FName GetActionName();


private:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName _actionName;

	UAction* _pNextAction;
	EActionState _state;
};
