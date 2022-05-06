// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MyDelegates.h"
#include "Condition/ConditionBase.h"
#include "Event/EventBroker.h"
#include "EventBrokerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UEventBrokerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEventBrokerComponent();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool RegisterEvent(FName eventName);
	bool ContainsRegisteredEvent(FName eventName);

	UFUNCTION(BlueprintCallable)
	bool PublishEvent(FName eventName, UObject* data);
	FMD_UObjectSignature* GetEventDelegate(FName eventName);
	FMD_UObjectSignature& RegisterAndGetEventDelegate(FName eventName);

	template<typename TData>
	FDelegateHandle SubscribeEvent(FName eventName, TData* inUserObj, void (TData::*InFunc)(UObject*));

private:
	UPROPERTY()
	UEventBroker* _eventBrokerIns;
};


template<typename TData>
FDelegateHandle UEventBrokerComponent::SubscribeEvent(FName eventName,TData* inUserObj,void (TData::* InFunc)(UObject*))
{
	FMD_UObjectSignature* eventDelegate = _eventBrokerIns->GetEventDelegate(eventName);
	if(eventDelegate)
	{
		(inUserObj->*InFunc)(_eventBrokerIns->GetCachedEventData(eventName));
		return eventDelegate->AddUObject<TData>(inUserObj, InFunc);
	}
	else
	{
		return FDelegateHandle();
	}
}