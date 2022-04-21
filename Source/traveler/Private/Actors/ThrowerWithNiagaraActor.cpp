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

	if (_impactedNiagaraEffectComp == nullptr)
	{
		_impactedNiagaraEffectComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("impactEffect"));
		check(_impactedNiagaraEffectComp != nullptr);
		_impactedNiagaraEffectComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
}

// Called when the game starts or when spawned
void AThrowerWithNiagaraActor::BeginPlay()
{
	Super::BeginPlay();

	//Initialize Particle
	if (_throwingNiagaraEffectComp)
	{
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::SpeedMax, _throwerData.Speed);
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::Life, _throwerData.Life);
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::SpriteScaleMin, _throwerData.Scale / 2.5);
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::SpriteScaleMax, _throwerData.Scale + 0.5f);
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::ConeAngle, _throwerData.ConeAngle);
		_throwingNiagaraEffectComp->SetVectorParameter(NSNameNiagaraParams::Gravity, _throwerData.Gravity);
	}
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
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::SpeedMax, speed);
	}
}

void AThrowerWithNiagaraActor::VSetLife(float life)
{
	Super::VSetLife(life);

	if (_throwingNiagaraEffectComp)
	{
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::Life, life);
	}
}

void AThrowerWithNiagaraActor::VSetSpawningActorScale(float scale)
{
	Super::VSetSpawningActorScale(scale);

	if (_throwingNiagaraEffectComp)
	{
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::SpriteScaleMin, scale / 2.5f);
		_throwingNiagaraEffectComp->SetFloatParameter(NSNameNiagaraParams::SpriteScaleMax, scale);
	}
}

void AThrowerWithNiagaraActor::VAutoDestroy()
{
	Super::VAutoDestroy();
	if(_throwingNiagaraEffectComp)
	{
		_throwingNiagaraEffectComp->Deactivate();
	}
}
