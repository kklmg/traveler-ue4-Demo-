// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EventPublisherComponent.generated.h"


//DECLARE_DELEGATE_TwoParams(FOnReceiveEvent, FName name,const UEventPublisherComponent&);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UEventPublisherComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEventPublisherComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//void SubscribeEvent(FName eventName);
	//void PublishEvent(FName eventName);

	//void RegisterObserver(FName eventName,UObject* NotifyOwner, FOnReceiveEvent ObserverDelegate);

};
