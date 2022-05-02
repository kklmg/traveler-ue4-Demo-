// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UOptionBase : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetID(int32 id);

	UFUNCTION(BlueprintCallable)
	void Scroll(int32 delta);

	UFUNCTION(BlueprintPure)
	virtual int32 VGetSize() PURE_VIRTUAL(UOptionBase::VGetSize, return 0;);

protected:
	int32 GetCurID();

private:
	UPROPERTY(EditDefaultsOnly)
	int32 _curID;
};

UCLASS(BlueprintType, Blueprintable)
class TRAVELER_API UIntOption : public UOptionBase
{
	GENERATED_BODY()

public:
	virtual int32 VGetSize() override;

	UFUNCTION(BlueprintCallable)
	int32 GetSelection();

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<int32> _options;
};


UCLASS(BlueprintType, Blueprintable)
class TRAVELER_API UFloatOption : public UOptionBase
{
	GENERATED_BODY()

public:
	virtual int32 VGetSize() override;

	UFUNCTION(BlueprintCallable)
	float GetSelection();

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<float> _options;
};
