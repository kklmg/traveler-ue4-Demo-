// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDMD_OnInt32ValueChanged, int32, NewValue);

/**
 * 
 */
UCLASS()
class TRAVELER_API ULevelStatus : public UObject
{
	GENERATED_BODY()
public:
	void SetLevel(int32 level, int32 exp = 0);
	UFUNCTION(BlueprintPure)
	int32 GetLevel();

private:
	int32 _level;
	int32 _exp;

public:
	UPROPERTY(BlueprintAssignable)
	FDMD_OnInt32ValueChanged OnLevelChanged;
};
