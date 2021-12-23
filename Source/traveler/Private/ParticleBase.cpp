// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleBase.h"
#include "NiagaraComponent.h"

// Sets default values
AParticleBase::AParticleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(!_nigaraComponent)
	{
		_nigaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
		check(_nigaraComponent != nullptr);
	}

}

// Called when the game starts or when spawned
void AParticleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

