// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/MyDelegates.h"
#include "LifeControlComponent.generated.h"

class UCompositeActorCondition;

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
	FMD_BoolValueChangeSignature* GetLifeChangedDelegate();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCompositeActorCondition> _lifeConditionClass;

	UPROPERTY()
	UCompositeActorCondition* _lifeConditionIns;
};
