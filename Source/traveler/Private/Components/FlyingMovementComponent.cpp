// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FlyingMovementComponent.h"

// Sets default values for this component's properties
UFlyingMovementComponent::UFlyingMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFlyingMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFlyingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFlyingMovementComponent::AddLocalPitch(float scale)
{
	_localPitchInput = _pitchRate * scale;
}

void UFlyingMovementComponent::AddLocalRoll(float scale)
{
	_localPitchInput = _rollRate * scale;
}

void UFlyingMovementComponent::AddWorldYaw(float scale)
{
	_worldYawInput = _yawRate * scale;
}

void UFlyingMovementComponent::ClearPitchRoll()
{
//FQuat 
}

