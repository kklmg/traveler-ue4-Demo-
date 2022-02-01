// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionWeaponStopAim.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionWeaponStopAim : public UActionBase
{
	GENERATED_BODY()
public:
	UActionWeaponStopAim();
protected:
	virtual void VTMExecute() override;
};
