// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/ThrowableInterface.h"
#include "ThrowerComponent.generated.h"

class IThrowerDataProviderInterface;

class AProjectileActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UThrowerComponent : public UActorComponent 
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThrowerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SpawnThrowingActor();

	UFUNCTION()
	bool isSpawnable();

	UFUNCTION()
	void StopSpawning();

	UFUNCTION()
	void OnSpawnedActorInactivated(int poolId);

	UFUNCTION()
	AProjectileActor* CreateOrGetInactivatedActor();

	void SphereTracing();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileActor> _spawningActorClass;

	UPROPERTY(EditDefaultsOnly)
	FTimerHandle _timerHandle;

	UPROPERTY(EditDefaultsOnly)
	int _poolSize;

	UPROPERTY()
	TArray<AProjectileActor*> _spawnedActors;

	UPROPERTY()
	TArray<int> _inactivatedActorIndicies;

	float _elapsedTime;
	IThrowerDataProviderInterface* _throwerDataProvider;
};
