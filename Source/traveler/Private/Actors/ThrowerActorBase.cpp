// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowerActorBase.h"

// Sets default values
AThrowerActorBase::AThrowerActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AThrowerActorBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto components = GetComponentsByInterface(UThrowerInterface::StaticClass());
	for (auto component : components)
	{
		_throwerInterfaces.Add(component);
	}

	VSetSpeed(_throwerData.Speed);
	VSetLife(_throwerData.Life);
	VSetSpawningActorScale(_throwerData.Scale);
}

// Called when the game starts or when spawned
void AThrowerActorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AThrowerActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AThrowerActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowerActorBase::VSetSpawningLocation(FVector location)
{
	SetActorLocation(location);
	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VSetSpawningLocation(location);
	}
}

void AThrowerActorBase::VSetThrowingDirection(FVector direction)
{
	SetActorRotation(direction.ToOrientationQuat());
	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VSetThrowingDirection(direction);
	}
}

void AThrowerActorBase::VSetSpawningActorScale(float scale)
{
	_throwerData.Scale = scale;
	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VSetSpawningActorScale(scale);
	}
}

void AThrowerActorBase::VSetSpeed(float speed)
{
	_throwerData.Speed = speed;
	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VSetSpeed(speed);
	}
}

void AThrowerActorBase::VSetLife(float life)
{
	_throwerData.Life = life;
	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VSetLife(life);
	}
}

FThrowerData AThrowerActorBase::VGetThrowerData()
{
	return _throwerData;
}

void AThrowerActorBase::VStartThrowing()
{
	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VStartThrowing();
	}
}

void AThrowerActorBase::VStopThrowing()
{
	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VStopThrowing();
	}
}

void AThrowerActorBase::MarkDestroy()
{
	SetLifeSpan(_throwerData.Life);

	for (auto throwerIntreface : _throwerInterfaces)
	{
		throwerIntreface->VStopThrowing();
	}
}
