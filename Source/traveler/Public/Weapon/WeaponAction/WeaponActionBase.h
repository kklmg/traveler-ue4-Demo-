// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "Actions/ActionBase.h"
#include "WeaponActionBase.generated.h"

class UWeaponComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UWeaponActionBase : public UActionBase
{
	GENERATED_BODY()

public:
	virtual void VSetUpActionData(ACharacter* character, UActionComponent* actionComp) override;
	virtual bool VCanExecute() override;

protected:
	UWeaponComponent* GetWeaponComp();

private:
	UPROPERTY()
	UWeaponComponent* _weaponComp;
};