// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableInterface.generated.h"

DECLARE_DELEGATE_OneParam(FOnObjectInactive,int32);

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
	virtual bool VActivate() PURE_VIRTUAL(IPoolableInterface::VActivate, return false; );
	virtual bool VInActivate() PURE_VIRTUAL(IPoolableInterface::VInActivate, return false; );

	virtual int VGetPoolId() PURE_VIRTUAL(IPoolableInterface::VGetPoolId, return 0;);
	virtual void VSetPoolId(int32 poolId) PURE_VIRTUAL(IPoolableInterface::VSetPoolId, );
	virtual void VMarkDestroy() PURE_VIRTUAL(IPoolableInterface::VMarkDestroy, );

	virtual FOnObjectInactive* VGetObjectInactiveDelegate() PURE_VIRTUAL(IPoolableInterface::VGetObjectInactiveDelegate,return nullptr;);
} ;
