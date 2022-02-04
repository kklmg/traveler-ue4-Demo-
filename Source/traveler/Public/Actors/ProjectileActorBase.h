// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/PoolableInterface.h"
#include "Interface/ThrowableInterface.h"
#include "ProjectileActorBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnActorInactivated, int)

class UProjectileMovementComponent;

UCLASS()
class TRAVELER_API AProjectileActorBase : public AActor, public IThrowableInterface, public IPoolableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//IPoolableInterface
	virtual bool VIsActive() override;
	virtual void VSetIsActive(bool isActive) override;
	virtual int VGetPoolId() final;
	virtual void VSetPoolId(int poolId) final;

	//IThrowableInterface
	virtual void VSetScale(float scale) override;
	virtual void VSetVelocity(FVector velocity) override;
	virtual void VSetLife(float life) override;
	virtual void VSetDamage(float damage) override;

protected:
	virtual void VOnActive();
	virtual void VOnInActive();

public:
	FOnActorInactivated OnActorInactivated;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* _rootSceneComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _meshComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* _projectileMovementComp;

	UPROPERTY(VisibleAnywhere)
	bool _isActive;

	UPROPERTY(VisibleAnywhere)
	float _elapsedTime;

	UPROPERTY(VisibleAnywhere)
	float _life;

	UPROPERTY(VisibleAnywhere)
	int _poolId;

	UPROPERTY(VisibleAnywhere)
	float _basicScale;

	UPROPERTY(VisibleAnywhere)
	float _damage;
};
