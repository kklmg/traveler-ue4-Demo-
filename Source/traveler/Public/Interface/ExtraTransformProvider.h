// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/EnumMeshSocketType.h"
#include "ExtraTransformProvider.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UExtraTransformProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IExtraTransformProvider
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual bool VTryGetSocketName(ETransform transformType, FName& outSocketName) PURE_VIRTUAL(UExtraTransformProvider::VTryGetSocketName, return false;);

	UFUNCTION(BlueprintCallable)
	virtual bool VTryGetTransform(ETransform meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform) PURE_VIRTUAL(UExtraTransformProvider::VTryGetTransform, return false;);
};
