// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ActorUIData.h"
#include "ActorWidget.generated.h"

class IExtraTransformProvider;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetData(AActor* widgetOwner,ETransform transformType);

	UFUNCTION(BlueprintCallable)
	AActor* GetWidgetOwner();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	AActor* _widgetOwner;

	UPROPERTY()
	ETransform _transformType;

	IExtraTransformProvider* _ExTransformProviderInterface;
};
