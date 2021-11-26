// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionData.h"
#include "Action.generated.h"

UENUM(BlueprintType)
enum class EActionState : uint8
{
	AS_UnInitialized UMETA(DisplayName = "UnInitialized"),
	AS_ReadyToExecute UMETA(DisplayName = "ReadyToExecute"),
	// Living processes
	AS_Running UMETA(DisplayName = "Running"),  // initialized and running
	AS_Paused UMETA(DisplayName = "Paused"),  // initialized but paused

	// Dead processes
	//AS_SUCCEEDED UMETA(DisplayName = "SUCCEEDED"),  // completed successfully
	//AS_FAILED UMETA(DisplayName = "FAILED"),  // failed to complete
	AS_Finished UMETA(DisplayName = "Finished"),
	AS_Aborted UMETA(DisplayName = "Aborted"),
};

namespace ActionName 
{
	const FName JUMP = FName(TEXT("jump"));
	const FName SPRINT = FName(TEXT("sprint"));
	const FName DODGE = FName(TEXT("dodge"));
	const FName MOVE = FName(TEXT("move"));
	const FName IDLE = FName(TEXT("idle"));
	const FName AIM = FName(TEXT("aim"));
}

class AMyCharacter;
class UActionComponent;


/**
 *
 */
UCLASS(Blueprintable)
class TRAVELER_API UAction : public UObject
{
	GENERATED_BODY()
public:
	UAction();
public:
	void Initialize(UActionComponent* actionComponent, UActionData* actionData);

	void Pause();
	void Abort();

	bool CanStart();
	EActionState GetState() const;
	//void SetState(EActionState state);

	bool IsInstantAction();

public:
	
	virtual void VExecute();
	virtual void VTick(float deltaTime);


public:
	FName GetActionName();

	ACharacter& GetActionOwner();

protected:
	UPROPERTY()
	ACharacter* _actionOwner;

	UPROPERTY()
	UActionData* _actionData;

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName _actionName;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool _bInstantAction;



	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UAction* _pNextAction;

	//UPROPERTY(VisibleAnywhere, Category = "Action")
	EActionState _state;
};
