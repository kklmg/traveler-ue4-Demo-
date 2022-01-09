// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/ThrowableInterface.h"
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

	void SetSpeed(float speed);
	void SetLife(float life);
	void SetScale(float scale);

	UFUNCTION()
	void SetThrowingOptions(float speed,float life,float rate);

	UFUNCTION()
	void SpawnThrowingActor();

	UFUNCTION()
	bool isSpawnable();

	UFUNCTION()
	void OnSpawnedActorInactivated(int poolId);

	UFUNCTION()
	AThrowableActor* CreateOrGetInactivatedActor();

	void SphereTracing();

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
	UCurveFloat* _scaleCurve;
	UPROPERTY(EditDefaultsOnly)
	float _coneAngle;
	UPROPERTY(EditDefaultsOnly)
	float _scale;

	UPROPERTY(EditDefaultsOnly)
	float _life;
	UPROPERTY(EditDefaultsOnly)
	int _poolSize;

	UPROPERTY(EditDefaultsOnly)
	float _damage;

	float _elapsedTime;

	UPROPERTY()
	TArray<AThrowableActor*> _spawnedActors;

	UPROPERTY()
	TArray<int> _inactivatedActorIndicies;
};
