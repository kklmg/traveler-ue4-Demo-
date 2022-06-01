// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/PostProcessControlBase.h"
#include "Interfaces/Interface_PostProcessVolume.h"
#include "PostProcess/PostProcessActor.h"

// Sets default values
APostProcessControlBase::APostProcessControlBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APostProcessControlBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APostProcessControlBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APostProcessControlBase::ActivateBlurEffect(bool bActive)
{
	if (_blurEffectActorClass == nullptr) return;

	if (bActive)
	{
		if (_blurEffectActorIns == nullptr)
		{
			_blurEffectActorIns = GetWorld()->SpawnActor<APostProcessActor>(_blurEffectActorClass);
		}
		_blurEffectActorIns->SetIsActive(true);
	}
	else
	{
		if (_blurEffectActorIns)
		{
			_blurEffectActorIns->SetIsActive(false);
		}
	}
}

