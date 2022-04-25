// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ProjectileActorBase.h"
#include "SphereProjectile.generated.h"

class UProjectileMovementComponent;
class UCurveFloat;



UCLASS()
class TRAVELER_API ASphereProjectile : public AProjectileActorBase 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void VSetScaleCurve(UCurveFloat* curve) override;

	UFUNCTION()
	virtual void VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void VApplyDamageToOverlapedActor();

	virtual void VOnActive() override;
	virtual void VOnInActive() override;

private:
	UPROPERTY(VisibleAnywhere)
	float _coneAngle;
	UPROPERTY(VisibleAnywhere)
	float _shift;
	UPROPERTY(VisibleAnywhere)
	FVector _initialMeshScale;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _scaleCurve;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TSubclassOf<UDamageType> _damageTypeClass;
};
