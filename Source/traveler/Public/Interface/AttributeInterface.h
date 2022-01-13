// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/CharacterAttribute.h"
#include "AttributeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UAttributeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IAttributeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable)
	virtual UCharacterAttribute* VGetAttribute(EAttributeType attributeType) PURE_VIRTUAL(IAttributeInterface::GetAttribute, return nullptr;);

	UFUNCTION(BlueprintCallable)
	virtual bool VSetAttribute(EAttributeType attributeType, float newValue) PURE_VIRTUAL(IAttributeInterface::SetAttribute, return false;);

	UFUNCTION(BlueprintCallable)
	virtual bool VSetAttributeChange(EAttributeType attributeType, float deltaValue) PURE_VIRTUAL(IAttributeInterface::SetAttributeChange, return false;);
};
