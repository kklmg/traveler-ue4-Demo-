// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ViewModel.h"
#include "AnimationModelBase.generated.h"

/**
 * 
 */

namespace AnimationDataKey
{
	const FName MovingDirection = FName(TEXT("MovingDirection"));
}

UCLASS()
class TRAVELER_API UAnimationModelBase : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UReactiveDataBase* GetData(FName dataKey);

	void SetInt(FName dataKey, int value);
	void SetFloat(FName dataKey, float value);
	void SetBool(FName dataKey, bool value);
	void SetVector(FName dataKey, FVector value);
	void SetQuat(FName dataKey, FQuat value);

private:
	UPROPERTY()
	TMap<FName,UReactiveDataBase*> _dataMap;
};
