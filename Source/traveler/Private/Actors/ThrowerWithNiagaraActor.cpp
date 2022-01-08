// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowerWithNiagaraActor.h"
#include "NiagaraComponent.h"

AThrowerWithNiagaraActor::AThrowerWithNiagaraActor()
{
	if (_throwingNiagaraEffectComp == nullptr)
	{
		_throwingNiagaraEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ThrowingEffect"));
		check(_throwingNiagaraEffectComp != nullptr);
		_throwingNiagaraEffectComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	if (_impactNiagaraEffectComp == nullptr)
	{
		_impactNiagaraEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("impactEffect"));
		check(_impactNiagaraEffectComp != nullptr);
		_impactNiagaraEffectComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
}

// Called when the game starts or when spawned
void AThrowerWithNiagaraActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AThrowerWithNiagaraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AThrowerWithNiagaraActor::VSetSpeed(float speed)
{
	Super::VSetSpeed(speed);

	if (_throwingNiagaraEffectComp)
	{
		_throwingNiagaraEffectComp->SetFloatParameter(NiagaraParameter::MaxSpeed, speed);
	}
}

void AThrowerWithNiagaraActor::VSetLife(float life)
{
	Super::VSetLife(life);

	if (_throwingNiagaraEffectComp)
	{
		_throwingNiagaraEffectComp->SetFloatParameter(NiagaraParameter::Life, life);
	}
}
