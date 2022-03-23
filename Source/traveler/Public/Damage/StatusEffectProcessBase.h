// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "UI/MyHUD.h"
#include "Data/StatusEffectData.h"
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
	void SetData(AActor* effectReceiver, UStatusEffectData* effectData);
	void CombineEffectData(UStatusEffectData* effectData);

protected:
	virtual void VTMInitialize() override;
	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual bool VIsInstantProcess() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;
	virtual void VTMReset() override;

	void SpawnEffectActor();
	void DestroyEffectActor();

private:
	bool _bHasDamage;

	float _totalElapsedTime;
	float _ElapsedTimeFromLastDamage;

	float _damage;
	float _damageInterval;
	float _damageDuration;
	EStatusEffect _statusEffectType;

	UPROPERTY()
	TSubclassOf<AActor> _effectActorClass;

	UPROPERTY()
	AActor* _effectActorIns;

	UPROPERTY()
	AActor* _effectReceiver;

	UPROPERTY()
	AMyHUD* _hud;

	UPROPERTY()
	UDamageHandlerComponent* _damageHandler;

	IAttributeInterface* _attributeInterface;
	IActorUIInterface* _UIInterface;
};
