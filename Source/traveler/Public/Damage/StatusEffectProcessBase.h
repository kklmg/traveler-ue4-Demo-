// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "UI/MyHUD.h"
#include "Data/StatusEffectData.h"
#include "StatusEffectProcessBase.generated.h"

class IAttributeInterface;
class IActorUIInterface;
class IActorEffectInterface;

class IDamageHandlerInterface;




/**
 * 
 */
UCLASS()
class TRAVELER_API UStatusEffectProcessBase : public UProcessBase
{
	GENERATED_BODY()

public:
	void SetData(AActor* effectReceiver, AActor* effectCauser, UStatusEffectData* effectData);
	void CombineEffectData(UStatusEffectData* effectData);

protected:
	virtual void VTMInitialize() override;
	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual bool VIsInstantProcess() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;
	virtual void VTMReset() override;

private:
	bool _bHasDamage;

	float _totalElapsedTime;
	float _ElapsedTimeFromLastDamage;

	float _damage;
	float _damageInterval;
	EDamageType _damageType;

	float _effectDuration;
	EStatusEffect _statusEffectType;

	UPROPERTY()
	AActor* _effectReceiver;

	UPROPERTY()
	AActor* _effectCauser;

	UPROPERTY()
	AMyHUD* _hud;

	IDamageHandlerInterface* _damageHandlerInterface;
	IActorEffectInterface* _actorEffectInterface;
	IActorUIInterface* _actorUIInterface;
};
