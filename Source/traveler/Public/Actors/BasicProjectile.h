// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ProjectileActorBase.h"
#include "BasicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API ABasicProjectile : public AProjectileActorBase
{
	GENERATED_BODY()
public:
	ABasicProjectile();
	
private:
	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type endPlayReason) override;

	void VSetVelocity(FVector velocity) override;
	virtual void VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
	void UpdatePredictDecal();

	UPROPERTY()
	UStaticMeshComponent* _staticMeshComp;

	UPROPERTY(EditDefaultsonly)
	TSubclassOf<AActor> _hitEffectActorClass;

	UPROPERTY(EditDefaultsonly)
	TSubclassOf<AActor> _groundEffectActorClass;

	UPROPERTY(EditDefaultsonly)
	TSubclassOf<AActor> _predictDecalActorClass;

	UPROPERTY()
	AActor* _predictDecalActorIns;
};
