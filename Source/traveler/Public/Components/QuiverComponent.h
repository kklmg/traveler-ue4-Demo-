// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuiverComponent.generated.h"

class AProjectileActorBase;


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

	void SpawnProjectiles(int count, APawn* instigator);

	void LaunchProjectiles(FVector Velocity);

private:
	AProjectileActorBase* CreateOrGetInactivatedFromPool();

	UFUNCTION()
	void OnSpawnedActorInactivated(int poolId);
private:
	UPROPERTY()
	TArray<AProjectileActorBase*> _projectilePool;

	UPROPERTY()
	TArray<int> _inactivatedIndicies;

	UPROPERTY(EditDefaultsOnly, Category = ProjectileClass)
	TSubclassOf<class AProjectileActorBase> _ProjectileClass;

	UPROPERTY()
	int _poolSize;

	UPROPERTY()
	int _projectileLife;
};
