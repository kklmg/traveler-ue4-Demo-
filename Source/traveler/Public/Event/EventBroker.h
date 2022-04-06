// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Event/EventDataBase.h"
#include "EventBroker.generated.h"




/**
 * 
 */
UCLASS()
class TRAVELER_API UEventBroker : public UObject
{
	GENERATED_BODY()

public:
	FMD_OnEventPublished& GetDelegate(FName eventName);
	void Publish(FName eventName, UEventDataBase* eventDataBase);

private:
	UPROPERTY()
	TMap<FName, FDelegateWrapper> _delegateMap;
};
