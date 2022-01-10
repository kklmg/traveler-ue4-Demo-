// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowerActor.h"
#include "Components/ThrowerComponent.h"

// Sets default values
AThrowerActor::AThrowerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (_rootComp == nullptr)
	{
		_rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
		check(_rootComp != nullptr);
		SetRootComponent(_rootComp);
	}

	if (_throwerComp == nullptr)
	{
		_throwerComp = CreateDefaultSubobject<UThrowerComponent>(TEXT("ThrowerComp"));
		check(_throwerComp != nullptr);
	}
}

// Called when the game starts or when spawned
void AThrowerActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AThrowerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AThrowerActor::VSetSpawningActorScale(float scale)
{
	_throwerData.Scale = scale;
}

void AThrowerActor::VSetSpeed(float speed)
{
	_throwerData.Speed = speed;
}

void AThrowerActor::VSetLife(float life)
{
	_throwerData.Life = life;
}

FThrowerData AThrowerActor::VGetThrowerData()
{
	return _throwerData;
}

