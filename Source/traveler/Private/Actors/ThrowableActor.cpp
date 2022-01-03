// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowableActor.h"

// Sets default values
AThrowableActor::AThrowableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThrowableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowableActor::VSetThrowingDirection(FVector dir)
{
	
}

void AThrowableActor::VSetSpeed(float speed)
{

}

void AThrowableActor::VSetLife(float life)
{

}

