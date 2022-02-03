// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionWeaponStopFire.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionWeaponStopFire : public UActionBase
{
	GENERATED_BODY()
public:
	UActionWeaponStopFire();
protected:
	virtual void VTMExecute() override;
};