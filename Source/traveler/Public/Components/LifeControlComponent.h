// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MyDelegates.h"
#include "Event/EventData.h"
#include "LifeControlComponent.generated.h"

class UDataBool;
class UCompositeActorCondition;
class UEventBrokerComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API ULifeControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULifeControlComponent();

	void InitializeComponent() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsAlive();

protected:
	void OnLifeStateChanged(bool isAlive);
	void OnActorDeathEffectFinished(UObject* baseData);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCompositeActorCondition> _lifeConditionClass;

	UPROPERTY(EditDefaultsOnly)
	bool _bDestroyAfterDead;

	UPROPERTY()
	UCompositeActorCondition* _ConditionIsAliveIns;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;

	UPROPERTY()
	UDataBool* _lifeStateChangedData;
};
