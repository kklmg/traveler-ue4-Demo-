// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponAction/WeaponActionBase.h"
#include "Weapon/BowBase.h"
#include "BowActionBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UBowActionBase : public UWeaponActionBase
{
	GENERATED_BODY()

public:
	virtual void VSetUpActionData(ACharacter* character, UActionComponent* actionComp);
	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;

protected:
	ABowBase* GetBow();

private:
	UPROPERTY()
	 ABowBase* _bow;
};
