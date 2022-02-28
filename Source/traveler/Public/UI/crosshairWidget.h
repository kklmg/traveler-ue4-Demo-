// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ContentWidget.h"
#include "crosshairWidget.generated.h"

/**
 *
 */


USTRUCT(BlueprintType)
struct FCrosshairElement
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FVector MovingDirection;

};



UCLASS()
class TRAVELER_API UcrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void Animate();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetDurationTime(float durationTime);

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FCrosshairElement> Elements;


private:

	UPROPERTY(EditAnyWhere)
	bool _bIsExpending;

	UPROPERTY(EditAnyWhere)
	float _durationTime;

	UPROPERTY(EditAnyWhere)
	UPanelWidget* widget;
};
