// Fill out your copyright notice in the Description page of Project Settings.


#include "Effet/EffectPlayerBase.h"
#include "Containers/Set.h"



UEffectPlayerBase::UEffectPlayerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UEffectPlayerBase::VInitialize(AActor* owner, UMaterialInstanceDynamic* mid)
{
	_owner = owner;
	_mid = mid;
}

void UEffectPlayerBase::VPlayEffect(uint8 effectOption)
{
}

void UEffectPlayerBase::VStopEffect(uint8 effectOption)
{
}

FORCEINLINE UMaterialInstanceDynamic* UEffectPlayerBase::GetMaterial()
{
	return _mid;
}

void UEffectPlayerBase::VTick(float deltaTime)
{
}

FORCEINLINE AActor* UEffectPlayerBase::GetOwner()
{
	return _owner;
}