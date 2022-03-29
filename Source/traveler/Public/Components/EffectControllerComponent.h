// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#incldue "Data/CombatData.h"
#include "EffectControllerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UEffectControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectControllerComponent();

	virtual void VPlayEffect(EStatusEffect effectType) override;
	virtual void VStopEffect(EStatusEffect effectType) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetUpMaterialInsDynamic(int32 elementIndex);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* _MID;
};
