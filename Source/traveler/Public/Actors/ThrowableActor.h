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

	virtual void VSetScale(float scale) override;
	virtual void VSetScaleCurve(UCurveFloat* curve) override;
	virtual void VSetVelocity(FVector velocity) override;
	virtual void VSetLife(float life) override;
	virtual void VSetDamage(float damage) override;

	UFUNCTION()
	virtual void VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual bool VIsActive() override;
	virtual void VSetIsActive(bool isActive) override;

	virtual int VGetPoolId();
	virtual void VSetPoolId(int poolId);

	virtual void VApplyDamageToOverlapedActor();

public:
	FOnActorInactivated OnActorInactivated;

private:
	bool _isActive;
	float _elapsedTime;
	float _life;
	int _poolId;
	float _coneAngle;
	float _shift;
	float _basicScale;
	float _damage;

	FVector _initialMeshScale;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _scaleCurve;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TSubclassOf<UDamageType> _damageTypeClass;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* _rootSceneComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* _meshComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* _projectileMovementComp;
};
