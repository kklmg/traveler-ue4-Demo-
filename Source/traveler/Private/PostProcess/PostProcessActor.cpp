// Fill out your copyright notice in the Description page of Project Settings.


#include "PostProcess/PostProcessActor.h"
#include "Components/PostProcessComponent.h"

// Sets default values
APostProcessActor::APostProcessActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_postProcessComp = CreateDefaultSubobject<UPostProcessComponent>(FName(TEXT("PostProcessComp")));
	check(_postProcessComp);

	SetRootComponent(_postProcessComp);
}

void APostProcessActor::SetIsActive(bool bActive)
{
	_postProcessComp->bEnabled = bActive;
}

// Called when the game starts or when spawned
void APostProcessActor::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void APostProcessActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


bool APostProcessActor::EncompassesPoint(FVector Point, float SphereRadius, float* OutDistanceToPoint)
{
	return _postProcessComp->EncompassesPoint(Point, SphereRadius, OutDistanceToPoint);
}

FPostProcessVolumeProperties APostProcessActor::GetProperties() const
{
	return _postProcessComp->GetProperties();
}


