// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MyDelegates.h"
#include "Condition/ConditionBase.h"
#include "EventBrokerComponent.generated.h"

class UEventBroker;

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

	UFUNCTION(BlueprintCallable)
	void PublishEvent(FName eventName, UObject* data);

	FMD_OnEventPublished& GetEventDelegate(FName eventName);

private:
	UPROPERTY()
	UEventBroker* _eventBroker;
};
