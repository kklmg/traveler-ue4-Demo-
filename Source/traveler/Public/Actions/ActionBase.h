// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EnumActionType.h"
#include "ActionBase.generated.h"



DECLARE_LOG_CATEGORY_EXTERN(LogAction, Log, All);

class IStateInterface;

UENUM(BlueprintType)
enum class EActionProcessState : uint8
{
	EAPS_UnInitialized UMETA(DisplayName = "UnInitialized"),
	EAPS_ReadyToExecute UMETA(DisplayName = "ReadyToExecute"),
	// Living processes
	EAPS_Running UMETA(DisplayName = "Running"),  // initialized and running
	EAPS_Paused UMETA(DisplayName = "Paused"),  // initialized but paused

	// Dead processes
	EAPS_SUCCEEDED UMETA(DisplayName = "SUCCEEDED"),  // execution succeed
	EAPS_FAILED UMETA(DisplayName = "FAILED"),  // execution failed 
	EAPS_Aborted UMETA(DisplayName = "Aborted"),
};

namespace ActionName
{
	const FName Throw = FName(TEXT("Throw"));
	const FName JUMP = FName(TEXT("jump"));
	const FName SPRINT = FName(TEXT("sprint"));
	const FName DODGE = FName(TEXT("dodge"));
	const FName MOVE = FName(TEXT("move"));
	const FName IDLE = FName(TEXT("idle"));
	const FName AIM = FName(TEXT("aim"));
	const FName ASCEND = FName(TEXT("ascend"));
	const FName FLY = FName(TEXT("fly"));
	const FName TAKEOFF = FName(TEXT("takeoff"));
	const FName TELEPORT = FName(TEXT("teleport"));
	const FName FlyTo = FName(TEXT("FlyTo"));
}

class UActionComponent;
class UActionBlackBoard;

/**
 *
 */
UCLASS(Blueprintable)
class TRAVELER_API UActionBase : public UObject
{
	GENERATED_BODY()
public:
	UActionBase();

public:
	UFUNCTION(BlueprintCallable)
	virtual bool VCanStart();

	UFUNCTION(BlueprintCallable)
	virtual void VExecute();

	virtual void VTick(float deltaTime);
public:
	void Initialize(UActionComponent* actionComponent, UActionBlackBoard* actionBlackBoard);

	UFUNCTION(BlueprintCallable)
	void Pause();

	UFUNCTION(BlueprintCallable)
	void Abort();

	UFUNCTION(BlueprintCallable)
	bool IsInstantAction();

	UFUNCTION(BlueprintCallable)
	FName GetActionName();

	UFUNCTION(BlueprintCallable)
	EActionType GetActionType();

	UFUNCTION(BlueprintCallable)
	bool IsCompleted();

	UFUNCTION(BlueprintCallable)
	EActionProcessState GetActionProcessState();

	UFUNCTION(BlueprintCallable)
	ACharacter* GetActionOwner();

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* GetActionBlackBoard();

protected:
	void SetActionSucceed();
	void SetActionFailed();

protected:
	virtual void _VOnActionCompleted();

	UPROPERTY()
	ACharacter* _actionOwner;

	UPROPERTY()
	UActionBlackBoard* _actionBlackBoard;

	UPROPERTY()
	UActionComponent* _actionComp;

	IStateInterface* _stateInterface;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName _actionName;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	EActionType _actionType;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool _bInstantAction;

	UPROPERTY(VisibleAnywhere, Category = "Action")
	EActionProcessState _processState;
};
