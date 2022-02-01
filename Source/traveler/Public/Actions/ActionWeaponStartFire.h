// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionWeaponStartFire.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionWeaponStartFire : public UActionBase
{
	GENERATED_BODY()
public:
	UActionWeaponStartFire();
protected:
	virtual void VTMExecute() override;
};
