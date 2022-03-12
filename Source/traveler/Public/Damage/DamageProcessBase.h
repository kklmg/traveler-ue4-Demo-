// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "Damage/MyDamageType.h"
#include "UI/MyHUD.h"
#include "DamageProcessBase.generated.h"

class IAttributeInterface;

/**
 * 
 */
 class UDamageHandlerComponent;

UCLASS()
class TRAVELER_API UDamageProcessBase : public UProcessBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetData(AActor* damageReceiver, UMyDamageType* damageType, FHitResult hitResult, AMyHUD* hud);

	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual FName VGetProcessName() override;
	virtual bool VIsInstantProcess() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;
	virtual void VTMReset() override;

private:
	float _elapsedTime;
	float _damageInterval;
	float _damageRemainCount;

	UPROPERTY()
	UMyDamageType* _damageType;

	UPROPERTY()
	AActor* _damageReceiver;

	UPROPERTY()
	FHitResult _hitResult;

	UPROPERTY()
	AMyHUD* _hud;

	UPROPERTY()
	UDamageHandlerComponent* _damageHandler;

	IAttributeInterface* _attributeInterface;
};
