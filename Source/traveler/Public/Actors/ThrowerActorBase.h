// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ThrowerInterface.h"
#include "Interface/ThrowerDataProviderInterface.h"
#include "ThrowerActorBase.generated.h"

UCLASS()
class TRAVELER_API AThrowerActorBase : public AActor,public IThrowerInterface,public IThrowerDataProviderInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowerActorBase();

protected:
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void VSetSpawningLocation(FVector location) override;
	virtual void VSetThrowingDirection(FVector direction) override;
	virtual void VSetSpawningActorScale(float scale) override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;
	virtual FThrowerData VGetThrowerData() override;
	virtual void VStartThrowing() override;
	virtual void VStopThrowing() override;

	virtual void MarkDestroy();

protected:
	UPROPERTY(EditDefaultsOnly, Category = ThrowerSetting)
	FThrowerData _throwerData;
private:
	UPROPERTY()
	TArray<TScriptInterface<IThrowerInterface>> _throwerInterfaces;
};
