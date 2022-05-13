// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessManagerBase.h"
#include "Enums/EnumCombat.h"
#include "StatusEffectProcessManager.generated.h"

class UStatusEffectProcessBase;
class UStatusEffectData;
class AMyHUD;
/**
 * 
 */
UCLASS()
class TRAVELER_API UStatusEffectProcessManager : public UObject
{
	GENERATED_BODY()
public:
	UStatusEffectProcessManager();

	UFUNCTION()
	void ExecuteProcess(AActor* effectReceiver, AActor* effectCauser, APawn* effectInstigator, UStatusEffectData* effectData);
	UStatusEffectProcessBase* StopProcess(EStatusEffect statusEffectType);

	bool IsExistStatusEffect(EStatusEffect statusEffectType);

	void Tick(float deltaTime);
protected:
	bool ApplyDurationChange(EStatusEffect statusEffectType,float deltaDuration);
	bool HandleElementalReaction(UStatusEffectData* statusEffectData);

private:
	UPROPERTY()
	TMap<EStatusEffect, UStatusEffectProcessBase*> _processMap;
};
