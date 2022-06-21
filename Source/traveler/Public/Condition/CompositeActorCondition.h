// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/CompositeCondition.h"
#include "CompositeActorCondition.generated.h"

class UActorCondition;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TRAVELER_API UCompositeActorCondition : public UCompositeCondition
{
	GENERATED_BODY()

public:
	void SetActor(AActor* actor);
protected:
	void VOnInitialized() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UActorCondition>> _actorConditionClasses;

	UPROPERTY()
	AActor* _actor;
};
