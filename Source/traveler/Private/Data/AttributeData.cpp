// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AttributeData.h"

// Sets default values
AAttributeData::AAttributeData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAttributeData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttributeData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float FAttributeRow::GetGrowedValue(int level)
{
	return value + GrowthRate * level;
}
