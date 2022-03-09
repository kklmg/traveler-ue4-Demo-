// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "Damage/MyDamageType.h"
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
	void SetData(AActor* actor, UMyDamageType* damageType);

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
	UDamageHandlerComponent* _damageHandler;

	IAttributeInterface* _attributeInterface;
};
