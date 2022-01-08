// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EnumActionType.h"
#include "ActionBase.generated.h"



DECLARE_LOG_CATEGORY_EXTERN(LogAction, Log, All);

UENUM(BlueprintType)
enum class EActionState : uint8
{
	AS_UnInitialized UMETA(DisplayName = "UnInitialized"),
	AS_ReadyToExecute UMETA(DisplayName = "ReadyToExecute"),
	// Living processes
	AS_Running UMETA(DisplayName = "Running"),  // initialized and running
	AS_Paused UMETA(DisplayName = "Paused"),  // initialized but paused

	// Dead processes
	AS_SUCCEEDED UMETA(DisplayName = "SUCCEEDED"),  // execution succeed
	AS_FAILED UMETA(DisplayName = "FAILED"),  // execution failed 
	AS_Aborted UMETA(DisplayName = "Aborted"),
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
	virtual void VExecute();
	virtual void VTick(float deltaTime);

public:
	void Initialize(UActionComponent* actionComponent, UActionBlackBoard* actionBlackBoard);

	UFUNCTION(BlueprintCallable)
	void Pause();

	UFUNCTION(BlueprintCallable)
	void Abort();

	UFUNCTION(BlueprintCallable)
	bool CanStart();

	UFUNCTION(BlueprintCallable)
	bool IsInstantAction();

	UFUNCTION(BlueprintCallable)
	FName GetActionName();

	UFUNCTION(BlueprintCallable)
	EActionType GetActionType();

	UFUNCTION(BlueprintCallable)
	bool IsCompleted();

	UFUNCTION(BlueprintCallable)
	EActionState GetActionState();

	UFUNCTION(BlueprintCallable)
	ACharacter* GetActionOwner();


protected:
	UFUNCTION(BlueprintCallable)
	void SetActionState(EActionState state);

	UPROPERTY()
	ACharacter* _actionOwner;

	UPROPERTY()
	UActionBlackBoard* _actionBlackBoard;

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName _actionName;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	EActionType _actionType;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool _bInstantAction;

	UPROPERTY(VisibleAnywhere, Category = "Action")
	EActionState _state;
};