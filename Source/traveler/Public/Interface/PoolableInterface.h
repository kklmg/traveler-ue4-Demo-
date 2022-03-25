// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableInterface.generated.h"


DECLARE_DELEGATE_OneParam(FOnPoolObjectDie,int32);

static FOnPoolObjectDie tempDelegate;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPoolableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IPoolableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool VIsActive() PURE_VIRTUAL(IPoolableInterface::VIsActive, return false; );
	virtual void VSetIsActive(bool isActive) PURE_VIRTUAL(IPoolableInterface::VSetIsActive, );

	virtual int VGetPoolId() PURE_VIRTUAL(IPoolableInterface::VGetPoolId, return 0;);
	virtual void VSetPoolId(int32 poolId) PURE_VIRTUAL(IPoolableInterface::VSetPoolId, );
	virtual FOnPoolObjectDie& VGetPoolObjectDieDelegate() PURE_VIRTUAL(IPoolableInterface::VGetPoolObjectDieDelegate,return tempDelegate;);
};
