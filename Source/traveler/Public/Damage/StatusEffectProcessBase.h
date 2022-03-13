// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "UI/MyHUD.h"
#include "StatusEffectProcessBase.generated.h"

class IAttributeInterface;
class IActorUIInterface;

class UDamageHandlerComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UStatusEffectProcessBase : public UProcessBase
{
	GENERATED_BODY()

public:
	void SetData(AActor* effectReceiver, AMyHUD* hud);

	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual FName VGetProcessName() override;
	virtual bool VIsInstantProcess() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;
	virtual void VTMReset() override;

private:
	bool _bHasDamage;

	float _elapsedTime;
	float _damageInterval;
	float _damageRemainCount;
	float _duration;


	UPROPERTY()
	AActor* _effectReceiver;

	UPROPERTY()
	AMyHUD* _hud;

	UPROPERTY()
	FName _effectName;

	UPROPERTY()
	UDamageHandlerComponent* _damageHandler;

	IAttributeInterface* _attributeInterface;
	IActorUIInterface* _UIInterface;
};
