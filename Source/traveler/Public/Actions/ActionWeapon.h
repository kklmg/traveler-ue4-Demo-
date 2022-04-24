// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionWeapon.generated.h"

/**
 *
 */
UCLASS()
class TRAVELER_API UActionWeapon : public UActionBase
{
	GENERATED_BODY()
public:
	UActionWeapon();

	virtual void VTMInit() override;
	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;
protected:
	UWeaponComponent* GetWeaponComp();

private:
	UFUNCTION()
	void OnWeaponChanged(AWeaponBase* weaponIns);

	UFUNCTION()
	void OnWeaponProcessStateChanged(EProcessState processState);

	UPROPERTY()
	UWeaponComponent* _weaponComp;

	UPROPERTY()
	UProcessBase* _weaponProcess;

	FDelegateHandle _delegateHandle;
};
