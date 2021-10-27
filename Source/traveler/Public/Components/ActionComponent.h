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

	void Move();
	void Sprint();
	void Jump();
	void Target();
	void Dash();

	void AddMovementInputX(float value);
	void AddMovementInputY(float value);

	void AddToLoop(UAction* action);
private:
	void _LoopActions(float deltaTime);

	FVector _CalculateMovingDirection();

private:
	TArray<UAction*> _actions;
	TMap<FName, UAction*> _MapActionsInProgress;

	UActionData* _actionData;

	FVector2D _movementInput;

	UPROPERTY(EditAnyWhere, Category = State)
	TSubclassOf<UCharacterStateBase> DefaultCharacterState;

	UCharacterStateBase* _pCharacterState;
};
