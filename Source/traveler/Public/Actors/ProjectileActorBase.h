// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/PoolableInterface.h"
#include "Interface/ThrowableInterface.h"
#include "Damage/DamageData.h"
#include "ProjectileActorBase.generated.h"


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
	virtual bool VIsActive() final;
	virtual bool VActivate() override;
	virtual bool VDeactivate() override;
	virtual int VGetPoolId() final;
	virtual void VSetPoolId(int poolId) final;
	virtual FOnObjectInactive* VGetObjectInactiveDelegate() final;
	virtual void VMarkDestroy() final;

	//IThrowableInterface
	virtual void VSetScale(float scale) override;
	virtual void VSetVelocity(FVector velocity) override;
	virtual void VSetLife(float life) override;
	virtual void VSetDamage(float damage) override;

	//virtual

	UFUNCTION()
	virtual void VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void VReset();
	virtual void FellOutOfWorld(const UDamageType& damageType) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* _rootSceneComp;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* _primitiveComp;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* _sphereComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* _projectileMovementComp;

	UPROPERTY(EditDefaultsOnly)
	FDamageData _damageData;

	UPROPERTY(VisibleAnywhere)
	bool _bIsMarkDead;

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

	FOnObjectInactive _OnObjectInactiveDelegate;
};
