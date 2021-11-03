// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionData.h"
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
	void Start(UActionComponent* actionComponent);

	void Pause();
	void Stop();

	bool CanStart();
	EActionState GetState() const;
	void SetState(EActionState state);

public:
	virtual void VInitialize();
public:
	virtual void VBegin(AActor* actor, UActionData* actionData) PURE_VIRTUAL(UAction::VBegin.;);
	virtual void VUpdate(float deltaTime,AActor* actor, UActionData *data) PURE_VIRTUAL(UAction::VUpdate.;);

public:
	FString GetActionName();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FString _actionName;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	UAction* _pNextAction;

	//UPROPERTY(VisibleAnywhere, Category = "Action")
	EActionState _state;
};
