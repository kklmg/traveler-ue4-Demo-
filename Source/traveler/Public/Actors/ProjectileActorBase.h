// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/PoolableInterface.h"
#include "Interface/ThrowableInterface.h"
#include "ProjectileActorBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnActorInactivated, int)

class USphereComponent;
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
	virtual void VActivate() override;
	virtual void VInActivate() override;
	virtual int VGetPoolId() final;
	virtual void VSetPoolId(int poolId) final;
	virtual FOnObjectInactive& VGetObjectInactiveDelegate() override;

	//IThrowableInterface
	virtual void VSetScale(float scale) override;
	virtual void VSetVelocity(FVector velocity) override;
	virtual void VSetLife(float life) override;
	virtual void VSetDamage(float damage) override;

protected:
	virtual void VOnActive();
	virtual void VOnInActive();
	virtual void VReset();

public:
	FOnActorInactivated OnActorInactivated;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* _rootSceneComp;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* _primitiveComp;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* _sphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* _projectileMovementComp;

	UPROPERTY(VisibleAnywhere)
	bool _bIsActive;

	UPROPERTY(VisibleAnywhere)
	float _elapsedLifeTime;

	UPROPERTY(VisibleAnywhere)
	bool _bIgnoreInstigator;

	UPROPERTY(EditDefaultsOnly)
	bool _bHasLife;

	UPROPERTY(EditDefaultsOnly)
	float _lifeTime;

	UPROPERTY(VisibleAnywhere)
	int _poolId;

	UPROPERTY(VisibleAnywhere)
	float _basicScale;

	UPROPERTY(VisibleAnywhere)
	float _damage;

	FOnObjectInactive _onOnjectInactive;
};
