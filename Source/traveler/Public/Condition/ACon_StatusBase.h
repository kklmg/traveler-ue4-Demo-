// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ActorCondition.h"
#include "Interface/StatusInterface.h"
#include "ACon_StatusBase.generated.h"

/**
 * 
 */

UCLASS()
class TRAVELER_API UACon_StatusBase : public UActorCondition
{
	GENERATED_BODY()
public:
	virtual void VSetActor(AActor* actor) override;
protected:
	virtual bool VTMValidate() override;

protected:
	IStatusInterface* _statusInterface;
};
