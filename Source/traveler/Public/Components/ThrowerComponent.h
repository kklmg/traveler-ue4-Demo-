// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/ThrowableInterface.h"
#include "ThrowerComponent.generated.h"

class AThrowableActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UThrowerComponent : public UActorComponent, public IThrowableInterface
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

	virtual void SetSpawningTransform(FTransform transform) override;
	virtual void VSetVelocity(FVector velocity);
	virtual void VSetLife(float life) override;

	UFUNCTION()
	void SetThrowingOptions(FVector velocity,float life,float rate);

	UFUNCTION()
	void SpawnThrowingActor();

	UFUNCTION()
	bool isSpawnable();

	UFUNCTION()
	void OnSpawnedActorInactivated(int poolId);

	UFUNCTION()
	AThrowableActor* CreateOrGetInactivatedActor();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AThrowableActor> _spawningActorClass;
	UPROPERTY(EditDefaultsOnly)
	FTimerHandle _timerHandle;
	UPROPERTY(EditDefaultsOnly)
	float _throwingRate;
	UPROPERTY(EditDefaultsOnly)
	FVector _velocity;

	UPROPERTY(EditDefaultsOnly)
	float _life;
	UPROPERTY(EditDefaultsOnly)
	int _poolSize;

	UPROPERTY()
	TArray<AThrowableActor*> _spawnedActors;

	UPROPERTY()
	TArray<int> _inactivatedActorIndicies;
};
