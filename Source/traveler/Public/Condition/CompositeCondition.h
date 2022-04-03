// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ConditionBase.h"
#include "CompositeCondition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class TRAVELER_API UCompositeCondition : public UConditionBase
{
	GENERATED_BODY()
public:
	virtual bool VValidate() override;

	void Initialize();
	void Add(UConditionBase* condition);
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UConditionBase>> _conditionClasses;

	UPROPERTY()
	TArray<UConditionBase*> _conditions;
};
