// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ThrowableActorBase.h"
#include "Interface/PoolableInterface.h"
#include "ThrowableActor.generated.h"

class UProjectileMovementComponent;
class UCurveFloat;

DECLARE_DELEGATE_OneParam(FOnActorInactivated, int)

UCLASS()
class TRAVELER_API AThrowableActor : public AThrowableActorBase , public IPoolableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	virtual void SetSpawningTransform(FTransform transform) override;
	virtual void VSetVelocity(FVector velocity) override;
	virtual void VSetLife(float life) override;
	virtual void VSetScaleCurve(UCurveFloat* curve) override;

	virtual bool VIsActive() override;
	virtual void VSetIsActive(bool isActive) override;

	virtual int VGetPoolId();
	virtual void VSetPoolId(int poolId);

public:
	FOnActorInactivated OnActorInactivated;

private:
	bool _isActive;
	float _elapsedTime;
	float _life;
	int _poolId;
	FTransform _spawnTransform;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _scaleCurve;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* _rootSceneComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* _projectileMovementComp;
};
