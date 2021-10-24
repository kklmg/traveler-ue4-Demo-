// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/Action.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

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

	void SetState();

	void Move(FVector direction,float scale = 1.0f);
	void Sprint();
	void Jump();
	void Target();
	void Dash();

	void AddMovementInputX(float value);
	void AddMovementInputY(float value);

private:
	TArray<UAction*> _actions;

	UCharacterStateBase *_pCharacterState;

	FVector2D _movementInput;
};
