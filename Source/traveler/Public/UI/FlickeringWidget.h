// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/UIProcess/UIProcessBase.h"
#include "FlickeringWidget.generated.h"

class UCompositeProcessBase;

class UFlickeringUIProcess;
class UProcessSectionBase;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTimeFrameFlickeringData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float  onRemainingTime;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float FlickeringDuration;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float CoolingDuration;
};

UCLASS()
class TRAVELER_API UFlickeringWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFlickeringWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float _flickeringDuration;

	UPROPERTY(EditAnywhere)
	float _coolingDuration;

	UPROPERTY(EditAnywhere)
	UCurveFloat* _opactiryCurve;

	UPROPERTY(EditAnywhere)
	TArray<FTimeFrameFlickeringData> _flickeringTimeLineData;

	int32 _currentTimeIndex;
	float _elapsedTime;
	float _duration;
private:
	

	UPROPERTY()
	UFlickeringUIProcess* _flickeringProcess;

	UPROPERTY()
	UProcessSectionBase* _coolingProcess;

	UPROPERTY()
	UCompositeProcessBase* _compositeProcess;
};
