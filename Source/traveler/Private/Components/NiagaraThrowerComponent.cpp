// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NiagaraThrowerComponent.h"

// Fill out your copyright notice in the Description page of Project Settings.

UNiagaraThrowerComponent::UNiagaraThrowerComponent()
{
}

void UNiagaraThrowerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNiagaraThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNiagaraThrowerComponent::VSetSpeed(float speed)
{
	SetFloatParameter(NSNameNiagaraParams::SpeedMax, speed);
}

void UNiagaraThrowerComponent::VSetLife(float life)
{
	SetFloatParameter(NSNameNiagaraParams::ParticleLife, life);
}

void UNiagaraThrowerComponent::VSetSpawningLocation(FVector location)
{
	
}

void UNiagaraThrowerComponent::VSetSpawningActorScale(float scale)
{
	SetFloatParameter(NSNameNiagaraParams::SpriteScaleMin, scale);
	SetFloatParameter(NSNameNiagaraParams::SpriteScaleMax, scale);
}

void UNiagaraThrowerComponent::VSetThrowingDirection(FVector direction)
{
}

void UNiagaraThrowerComponent::VStartThrowing()
{
	Activate();
}

void UNiagaraThrowerComponent::VStopThrowing()
{
	Deactivate();
}