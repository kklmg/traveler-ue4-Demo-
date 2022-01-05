// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/ThrowableInterface.h"



// Add default functionality here for any IThrowableInterface functions that are not pure virtual.

void IThrowableInterface::SetSpawningTransform(FTransform transform)
{
	UE_LOG(LogTemp, Warning, TEXT("IThrowableInterface::SetSpawningTransform is not implemented"));
}

void IThrowableInterface::VSetVelocity(FVector velocity)
{
	UE_LOG(LogTemp, Warning, TEXT("IThrowableInterface::VSetVelocity is not implemented"));
}

void IThrowableInterface::VSetLife(float life)
{
	UE_LOG(LogTemp, Warning, TEXT("IThrowableInterface::VSetLife is not implemented"));
}
