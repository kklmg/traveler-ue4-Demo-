// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Thrower.h"
#include "NiagaraComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ThrowerComponent.h"

// Sets default values
AThrower::AThrower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	if (_rootComp == nullptr)
	{
		_rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
		check(_rootComp != nullptr);
		SetRootComponent(_rootComp);
	}

	if (_throwingNiagaraEffectComp == nullptr)
	{
		_throwingNiagaraEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ThrowingEffect"));
		check(_throwingNiagaraEffectComp != nullptr);
		_throwingNiagaraEffectComp->AttachTo(_rootComp);
	}

	if (_impactNiagaraEffectComp == nullptr)
	{
		_impactNiagaraEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("impactEffect"));
		check(_impactNiagaraEffectComp != nullptr);
		_impactNiagaraEffectComp->AttachTo(_rootComp);
	}
	
	if (_throwerComp == nullptr)
	{
		_throwerComp = CreateDefaultSubobject<UThrowerComponent>(TEXT("ThrowerComp"));
		check(_throwerComp != nullptr);
	}

}

// Called when the game starts or when spawned
void AThrower::BeginPlay()
{
	Super::BeginPlay();

	_elapsedTime = 0.0f;
	_traceDistance = 0.0f;
	_traceSphereRadius = 0.0f;
	_MaxDistance = _maxSpeed * _life;

	
	if (_throwingNiagaraEffectComp)
	{
		_throwingNiagaraEffectComp->SetFloatParameter(NiagaraParameter::MaxSpeed, _maxSpeed);
		_throwingNiagaraEffectComp->SetFloatParameter(NiagaraParameter::Life, _life);
	}
}

// Called every frame
void AThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_elapsedTime += DeltaTime;
	_traceDistance = FMath::Clamp(_traceDistance + _maxSpeed * DeltaTime, 0.0f, _MaxDistance);

	
	_traceSphereRadius = _sizeCurve ? _sizeCurve->GetFloatValue(_elapsedTime / _life) : 10.0f;

	FVector traceStart = GetActorLocation();
	FVector traceDir = GetActorQuat().Vector();
	FVector traceEnd = traceStart + traceDir * _traceDistance;

	TArray<AActor*> ignoredActors;
	ignoredActors.Add(GetOwner());

	TArray<FHitResult> hitResults;

	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), traceStart, traceEnd, _traceSphereRadius,
		ETraceTypeQuery::TraceTypeQuery1, false, ignoredActors, EDrawDebugTrace::ForOneFrame, hitResults, true);

	for (FHitResult hitRes : hitResults)
	{
		if (hitRes.Actor == nullptr)
		{
			continue;
		}
		FDamageEvent damageEvent;
		APawn* instigator = GetInstigator();
		hitRes.Actor->TakeDamage(_damage, damageEvent, instigator ? instigator->GetController() : nullptr, instigator);
	}
}

void AThrower::SetSpawningTransform(FTransform transform)
{
	SetActorTransform(transform);
}

void AThrower::VSetVelocity(FVector velocity)
{
	if (_throwerComp)
	{
		_throwerComp->VSetVelocity(velocity);
	}
}

void AThrower::VSetLife(float life)
{
	if (_throwerComp)
	{
		_throwerComp->VSetLife(life);
	}
}

