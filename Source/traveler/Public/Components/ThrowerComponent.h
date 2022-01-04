// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowerComponent.generated.h"

class AThrowableActor;

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
	void SetThrowingOptions(FVector direction,float speed, float life,float rate);

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
	float _speed;
	UPROPERTY(EditDefaultsOnly)
	FVector _direction;
	UPROPERTY(EditDefaultsOnly)
	float _life;
	UPROPERTY(EditDefaultsOnly)
	int _poolSize;

	UPROPERTY()
	TArray<AThrowableActor*> _spawnedActors;

	UPROPERTY()
	TArray<int> _inactivatedActorIndicies;
};
