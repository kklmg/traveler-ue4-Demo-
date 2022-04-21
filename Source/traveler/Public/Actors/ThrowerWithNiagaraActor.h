// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ThrowerActor.h"
#include "ThrowerWithNiagaraActor.generated.h"

class UNiagaraComponent;

namespace NSNameNiagaraParams
{
	const FName SpeedMax(TEXT("SpeedMax"));
	const FName SpeedMin(TEXT("SpeedMin"));
	const FName Gravity(TEXT("Gravity"));
	const FName ConeAngle(TEXT("ConeAngle"));
	const FName Life(TEXT("ParticleLife"));
	const FName SizeCurve(TEXT("sizeCurve"));
	const FName SpriteScaleMin(TEXT("SpriteScaleMin"));
	const FName SpriteScaleMax(TEXT("SpriteScaleMax"));
}

/**
 * 
 */
UCLASS()
class TRAVELER_API AThrowerWithNiagaraActor : public AThrowerActor
{
	GENERATED_BODY()
public:
	AThrowerWithNiagaraActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;
	virtual void VSetSpawningActorScale(float scale) override;

	virtual void VAutoDestroy() override;

private:
	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* _throwingNiagaraEffectComp;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* _impactedNiagaraEffectComp;
};
