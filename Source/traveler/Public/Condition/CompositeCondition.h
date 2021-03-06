// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ConditionBase.h"
#include "CompositeCondition.generated.h"

/**
 * 
 */

UCLASS()
class TRAVELER_API UCompositeCondition : public UConditionBase
{
	GENERATED_BODY()
public:
	void Add(UConditionBase* condition);
	void OnSubConditionChanged(bool result);

protected:
	void VOnInitialized() override;
	virtual bool VOnValidated() override;
	

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UConditionBase>> _conditionClasses;

	UPROPERTY()
	TArray<UConditionBase*> _conditions;
};
