// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "UI/MyHUD.h"
#include "Data/StatusEffectData.h"
#include "StatusEffectProcessBase.generated.h"


class UDamageHandlerComponent;
class UActorUIComponent;
class UEffectControllerComponent;

class IDamageHandlerInterface;




/**
 * 
 */
UCLASS()
class TRAVELER_API UStatusEffectProcessBase : public UProcessBase
{
	GENERATED_BODY()

public:
	UStatusEffectProcessBase();

	void SetData(AActor* effectReceiver, AActor* effectCauser, APawn* effectInstigator, UStatusEffectData* effectData);
	void ApplyDurationChange(float deltaDuration);
	float GetRemainingTime();

protected:
	virtual void VOnInit() override;
	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;
	virtual void VOnDead() override;

private:
	bool _bHasDamage;

	float _remainingTime;
	float _ElapsedTimeFromLastDamage;

	float _damage;
	EElementalType _elementalType;
	float _damageInterval;

	EStatusEffect _statusEffectType;

	UPROPERTY()
	AActor* _effectReceiver;

	UPROPERTY()
	AActor* _effectCauser;

	UPROPERTY()
	APawn* _effectInstigator;

	UPROPERTY()
	AMyHUD* _hud;

	UPROPERTY()
	UDamageHandlerComponent* _damageHandlerComp;
	UPROPERTY()
	UEffectControllerComponent* _effectControlComp;
	UPROPERTY()
	UActorUIComponent* _actorUIComp;

	float _maxDuration;
};
