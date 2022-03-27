// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuiverComponent.generated.h"

class AArrowActorBase;
class UObjectPoolBase;

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
	UPROPERTY()
	UObjectPoolBase* _arrowPool;

	UPROPERTY(EditDefaultsOnly)
	int32 _poolSize;

	UPROPERTY(EditDefaultsOnly, Category = ArrowClass)
	TSubclassOf<AArrowActorBase> _arrowClass;
};
