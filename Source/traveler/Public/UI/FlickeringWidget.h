// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/UIProcess/UIProcessBase.h"
#include "FlickeringWidget.generated.h"

class UCompositeProcessBase;

/**
 * 
 */

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
	float _flickeringTime;

	UPROPERTY(EditAnywhere)
	float _coolingTime;

	UPROPERTY(EditAnywhere)
	UCurveFloat* _opactiryCurve;

	float _elapsedTime;
private:
	UCompositeProcessBase* _compositeProcess;
};
