// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "Components/Widget.h"
#include "UIProcessBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UUIProcessBase : public UProcessBase
{
	GENERATED_BODY()
public:
	void SetWidget(UWidget* widget);
	UWidget* GetWidget();

private:
	UWidget* _widget;
};
