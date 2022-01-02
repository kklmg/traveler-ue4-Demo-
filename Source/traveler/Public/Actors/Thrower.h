// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Thrower.generated.h"

class UCurveFloat;
class USceneComponent;
class UNiagaraComponent;

namespace NiagaraParameter
{
	const FName MaxSpeed(TEXT("MaxSpeed"));
	const FName Life(TEXT("ParticleLife"));
	const FName SizeCurve(TEXT("sizeCurve"));

}

UCLASS()
class TRAVELER_API AThrower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float _maxSpeed;
	UPROPERTY(EditDefaultsOnly)
	float _life;
	UPROPERTY(EditDefaultsOnly)
	float _damage;
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat *_sizeCurve;
	

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

};
