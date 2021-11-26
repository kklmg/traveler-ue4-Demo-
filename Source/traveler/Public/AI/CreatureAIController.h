// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CreatureAIController.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API ACreatureAIController : public AAIController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;




	UPROPERTY(EditDefaultsOnly, Category = AI)
	UBehaviorTree* _behaviorTree;
};
