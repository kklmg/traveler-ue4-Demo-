// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuiverComponent.generated.h"

class AArrowActorBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UQuiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnArrows(int count, APawn* instigator,TArray<AArrowActorBase*>& outArray);
private:
	AArrowActorBase* CreateOrGetInactivatedFromPool();

	//UFUNCTION()
	void OnSpawnedActorInactivated(int poolId);
private:
	//UPROPERTY()
	TArray<AArrowActorBase*> _arrowPool;
	//UPROPERTY()
	TArray<int> _inactivatedIndicies;

	UPROPERTY(EditDefaultsOnly, Category = ArrowClass)
	TSubclassOf<class AArrowActorBase> _arrowClass;

	//UPROPERTY()
	int _poolSize;
};
