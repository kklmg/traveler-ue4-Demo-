// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ThrowerActorBase.h"
#include "Components/SceneComponent.h"
#include "ThrowerActor.generated.h"

class UCurveFloat;
class USceneComponent;
class UNiagaraComponent;
class UThrowerComponent;

namespace NiagaraParameter
{
	const FName MaxSpeed(TEXT("MaxSpeed"));
	const FName Life(TEXT("ParticleLife"));
	const FName SizeCurve(TEXT("sizeCurve"));

}

UCLASS()
class TRAVELER_API AThrowerActor : public AThrowerActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void VSetSpawningLocation(FVector location) override;
	virtual void VSetThrowingDirection(FVector direction) override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float _maxSpeed;
	UPROPERTY(EditDefaultsOnly)
	float _life;
	UPROPERTY(EditDefaultsOnly)
	float _damage;
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *_scaleCurve;
	

	float _elapsedTime;
	float _traceDistance;
	float _MaxDistance;
	float _traceSphereRadius;


private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* _rootComp;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* _throwingNiagaraEffectComp;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* _impactNiagaraEffectComp;

	UPROPERTY(VisibleAnywhere)
	UThrowerComponent* _throwerComp;
	
};
