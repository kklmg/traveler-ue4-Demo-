// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/UIProcess/UIProcessBase.h"
#include "FlickeringWidget.generated.h"

class UCompositeProcessBase;

class UFlickeringUIProcess;
class UProcessSectionBase;
class UImage;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTimeNodeData_Flickering
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float RemainingTime;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float FlickeringDuration;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float CoolingDuration;
};

USTRUCT(BlueprintType)
struct FFlickeringWidgetData
{
	GENERATED_USTRUCT_BODY()
public:
	FFlickeringWidgetData();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float MaxDuration;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	UCurveFloat* OpacityCurve;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TArray<FTimeNodeData_Flickering> FlickeringTimeLineData;
};




UCLASS()
class TRAVELER_API UFlickeringWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFlickeringWidget(const FObjectInitializer& ObjectInitializer);
	
	void Tick(float deltaTime);
	void SetData(FFlickeringWidgetData& widgetData);
	void SetDuration(float duration);
	void ExecuteFlickeringProcess();
	void Reset();

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	
	virtual void UpdateFlickering();


private:
	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UImage* imgProgressBar;

	UPROPERTY()
	UFlickeringUIProcess* _flickeringProcess;

	UPROPERTY()
	UProcessSectionBase* _coolingProcess;

	UPROPERTY()
	UCompositeProcessBase* _compositeProcess;

	UPROPERTY()
	FFlickeringWidgetData _widgetData;

	int32 _curTimeNodeID;
	float _remainingTime;
};
