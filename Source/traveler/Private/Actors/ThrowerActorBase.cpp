// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowerActorBase.h"

// Sets default values
AThrowerActorBase::AThrowerActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThrowerActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowerActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowerActorBase::VSetSpawningLocation(FVector location)
{
	SetActorLocation(location);
}

void AThrowerActorBase::VSetThrowingDirection(FVector direction)
{
	SetActorRotation(direction.ToOrientationQuat());
}
