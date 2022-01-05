// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowableActorBase.h"

// Sets default values
AThrowableActorBase::AThrowableActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThrowableActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

