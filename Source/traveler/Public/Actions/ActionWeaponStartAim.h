// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionWeaponStartAim.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionWeaponStartAim : public UActionBase
{
	GENERATED_BODY()
public:
	UActionWeaponStartAim();

	virtual void VInitialize(ACharacter* character, UActionComponent* actionComp, UActionBlackBoard* actionBlackBoard);
protected:
	virtual void VTMExecute() override;	
};
