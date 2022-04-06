// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/CostData.h"
#include "Status/BasicStatus.h"
#include "Status/LevelStatus.h"
#include "StatusInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UStatusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRAVELER_API IStatusInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual int32 VGetLevelValue() PURE_VIRTUAL(IStatusInterface::VGetLevelValue, return 1;);
	UFUNCTION(BlueprintCallable)
	virtual ULevelStatus* VGetLevelStatusIns() PURE_VIRTUAL(IStatusInterface::VGetLevelStatusIns, return nullptr;);

	UFUNCTION(BlueprintCallable)
	virtual float VGetPrimaryValue(EStatusType statusType) PURE_VIRTUAL(IStatusInterface::VGetPrimaryValue, return 0.0f;);
	UFUNCTION(BlueprintCallable)
	virtual float VGetBasicValue(EStatusType statusType) PURE_VIRTUAL(IStatusInterface::VGetBasicValue, return 0.0f;);
	UFUNCTION(BlueprintCallable)
	virtual float VGetFinalValue(EStatusType statusType) PURE_VIRTUAL(IStatusInterface::VGetFinalValue, return 0.0f;);
	UFUNCTION(BlueprintCallable)
	virtual float VGetRemainingValue(EStatusType statusType) PURE_VIRTUAL(IStatusInterface::VGetRemainingValue, return 0.0f;);

	UFUNCTION(BlueprintCallable)
	virtual UStatusBase* VGetStatusIns(EStatusType statusType) PURE_VIRTUAL(IStatusInterface::VGetStatusIns, return nullptr;);
	UFUNCTION(BlueprintCallable)
	virtual UBasicStatus* VGetBasicStatusIns(EStatusType statusType) PURE_VIRTUAL(IStatusInterface::VGetBasicStatusIns, return nullptr;);

	UFUNCTION(BlueprintCallable)
	virtual void VApplyRemainingValueChange(EStatusType statusType, float value) PURE_VIRTUAL(IStatusInterface::VApplyRemainingValueChange,);
	UFUNCTION(BlueprintCallable)
	virtual bool VIsRemainingValueEnough(UCostData* costData) PURE_VIRTUAL(IStatusInterface::VIsRemainingValueEnough,return false;);
	UFUNCTION(BlueprintCallable)
	virtual bool VApplyCost(UCostData* costData) PURE_VIRTUAL(IStatusInterface::VApplyCost, return false;);
};
