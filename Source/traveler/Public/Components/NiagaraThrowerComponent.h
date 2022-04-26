// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Interface/ThrowerInterface.h"
#include "NiagaraThrowerComponent.generated.h"

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
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRAVELER_API UNiagaraThrowerComponent : public UNiagaraComponent, public IThrowerInterface
{
	GENERATED_BODY()
public:
	UNiagaraThrowerComponent();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void VSetSpawningLocation(FVector location) override;
	virtual void VSetSpawningActorScale(float scale) override;
	virtual void VSetThrowingDirection(FVector direction) override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;
	virtual void VStartThrowing() override;
	virtual void VStopThrowing() override;
};