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
	
	void SetDuration(float duration);
	void SetOpacityCurve(UCurveFloat* curve);
	void SetTimeLineData(TArray<FTimeFrameFlickeringData> timeLineData); 
	void ExecuteFlickeringProcess();
	void Reset();

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


private:
	UPROPERTY()
	UCurveFloat* _opacityCurve;

	UPROPERTY()
	TArray<FTimeFrameFlickeringData> _flickeringTimeLineData;

	UPROPERTY()
	UFlickeringUIProcess* _flickeringProcess;

	UPROPERTY()
	UProcessSectionBase* _coolingProcess;

	UPROPERTY()
	UCompositeProcessBase* _compositeProcess;

	int32 _currentTimeIndex;

	float _elapsedTime;

	float _duration;
};
