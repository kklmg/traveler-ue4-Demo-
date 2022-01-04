// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/PoolableInterface.h"

// Add default functionality here for any IPoolableInterface functions that are not pure virtual.

bool IPoolableInterface::VIsActive()
{
	UE_LOG(LogTemp, Warning, TEXT("IPoolableInterface::VIsActive is not implemented"));
	return false;
}

void IPoolableInterface::VSetIsActive(bool isActive)
{
	UE_LOG(LogTemp, Warning, TEXT("IPoolableInterface::VSetIsActive is not implemented"));
}

int IPoolableInterface::VGetPoolId()
{
	UE_LOG(LogTemp, Warning, TEXT("IPoolableInterface::VGetPoolId is not implemented"));
	return 0;
}

void IPoolableInterface::VSetPoolId(int poolId)
{
	UE_LOG(LogTemp, Warning, TEXT("IPoolableInterface::VSetPoolId is not implemented"));
}
