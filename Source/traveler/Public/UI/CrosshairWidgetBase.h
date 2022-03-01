// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ContentWidget.h"
#include "CrosshairWidgetBase.generated.h"

class UImage;
class UAnimatedImageBase;

/**
 *
 */


//UENUM(BlueprintType)
//enum class EScreenLocation : uint8
//{
//	EScreenLoc_Center UMETA(DisplayName = "Center"),
//
//	EScreenLoc_Left UMETA(DisplayName = "Left"),
//	EScreenLoc_Right UMETA(DisplayName = "Right"),
//	EScreenLoc_Top UMETA(DisplayName = "Top"),
//	EScreenLoc_Bottom UMETA(DisplayName = "Bottom"),
//
//	EScreenLoc_LeftTop UMETA(DisplayName = "LeftTop"),
//	EScreenLoc_LeftBottom UMETA(DisplayName = "LeftBottom"),
//	EScreenLoc_RightTop UMETA(DisplayName = "RightTop"),
//	EScreenLoc_RightBottom UMETA(DisplayName = "RightBottom"),
//};



USTRUCT(BlueprintType)
struct FCrosshairElement
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnyWhere)
	FVector StartLocation;

	UPROPERTY(EditAnyWhere)
	FVector EndLocation;

	UPROPERTY(BlueprintReadOnly)
	FVector CurrentLocation;

	UPROPERTY(EditAnyWhere)
	FRotator StartRotation;

	UPROPERTY(EditAnyWhere)
	FRotator EndRotation;

	UPROPERTY(BlueprintReadOnly)
	FRotator CurrentRotation;
};



UCLASS()
class TRAVELER_API UCrosshairWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	void Animate(float deltaTime, bool isForward);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetDurationTime(float durationTime);

public:
	UPROPERTY(EditAnyWhere,BlueprintReadOnly, Instanced)
	TArray<UAnimatedImageBase*> AnimElements;

private:
	UPROPERTY(EditAnyWhere)
	float _durationTime;

	UPROPERTY(EditAnyWhere)
	UPanelWidget* widget;

	float _elapsedTime;
};