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
	void SetData(AActor* effectReceiver, AActor* effectCauser, APawn* effectInstigator, UStatusEffectData* effectData);
	void CombineEffectData(UStatusEffectData* effectData);

protected:
	virtual void VTMInit() override;
	virtual bool VCanExecute() override;
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;

private:
	bool _bHasDamage;

	float _totalElapsedTime;
	float _ElapsedTimeFromLastDamage;

	float _damage;
	EElementalType _elementalType;
	float _damageInterval;

	float _effectDuration;
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
};
