// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

class UAction;
class UActionData;
class UCharacterStateBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetCharacterState();

	void OnJumpButtonDown();
	void OnJumpButtonUp();

	void OnSprintButtonDown();
	void OnSprintButtonUp();

	void TriggerIdle();
	void TriggerMove();
	void TriggerSprint();
	void TriggerJump();
	void TriggerTarget();
	void TriggerDash();

	void AddMovementInputX(float value);
	void AddMovementInputY(float value);

	void AddToLoop(UAction* action);

	void OnCharacterMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

public:
	UActionData* GetActionData();

	void ExecuteAction(FName actionName);

	void ClearActionProcessPool();

private:
	void _TickActionProcess(float deltaTime);

	FVector _CalculateMovingDirection();

private:
	//TArray<UAction*> _arrayActionsInProgress;
	UPROPERTY()
	TMap<FName, UAction*> _mapActionProcessPool;

	UPROPERTY()
	UActionData* _actionData;


//	TAarray<>


	FVector2D _movementInput;

	UPROPERTY(EditDefaultsOnly, Category = State)
	TSubclassOf<UCharacterStateBase> DefaultCharacterStateClass;

	UPROPERTY(EditDefaultsOnly, Category = State)
	TMap<TEnumAsByte<EMovementMode>, TSubclassOf<UCharacterStateBase>> _mapActionGroup;

	UPROPERTY()
	UCharacterStateBase* _pCurrentCharacterState;

	bool _bSprintButtonPress;
};
