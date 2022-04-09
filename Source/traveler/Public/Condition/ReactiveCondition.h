// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/CompositeCondition.h"
#include "ReactiveCondition.generated.h"

class IEventBrokerInterface;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnValidateCondition, bool);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class TRAVELER_API UReactiveCondition : public UCompositeCondition
{
	GENERATED_BODY()
public:
	void SubscribeEvents(IEventBrokerInterface* eventBroker);

	virtual bool VValidate(UEventDataBase* eventData) override;

protected:
	void Notify(UEventDataBase* eventData);

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FName> _eventNames;

public:
	FOnValidateCondition OnValidate;
};
