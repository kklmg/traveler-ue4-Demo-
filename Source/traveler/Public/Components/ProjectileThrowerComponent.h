// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ThrowerData.h"
#include "Interface/ThrowableInterface.h"
#include "Interface/ThrowerInterface.h"
#include "ProjectileThrowerComponent.generated.h"

class IThrowerDataProviderInterface;

class AProjectileActorBase;
class ASphereProjectile;
class UObjectPoolBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UProjectileThrowerComponent : public UActorComponent , public IThrowerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileThrowerComponent();

protected:
	virtual void InitializeComponent() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void VSetSpawningLocation(FVector location) override;
	virtual void VSetSpawningActorScale(float scale) override;
	virtual void VSetThrowingDirection(FVector direction)override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;
	virtual void VAutoDestroy() override;


	UFUNCTION()
	void SpawnProjectile();

	UFUNCTION()
	bool isSpawnable();

	UFUNCTION()
	void StopSpawning();

	void SphereTracing();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileActorBase> _spawningActorClass;

	UPROPERTY(EditDefaultsOnly)
	FTimerHandle _timerHandle;

	UPROPERTY()
	UObjectPoolBase* _pool;

	UPROPERTY(EditDefaultsOnly)
	int32 _poolSize;

	FThrowerData _throwerData;

	float _elapsedTime;
};
