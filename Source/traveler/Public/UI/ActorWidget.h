// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ActorUIData.h"
#include "ActorWidget.generated.h"

class UExTransformProviderComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDMD_OnActorChanged,AActor*,actor);

/**
 * 
 */
UCLASS()
class TRAVELER_API UActorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UActorWidget(const FObjectInitializer& ObjectInitializer);

	void SetData(AActor* widgetOwner,ETransform transformType);

	UFUNCTION(BlueprintPure)
	AActor* GetWidgetOwner();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	AActor* _widgetOwner;

	UPROPERTY()
	ETransform _transformType;

	UPROPERTY(EditDefaultsOnly)
	float _timeCollapse;
	float _elapsedTime_LeaveScreen;

	UPROPERTY(EditDefaultsOnly)
	float _renderScaleMax;
	UPROPERTY(EditDefaultsOnly)
	float _renderScaleMin;
	UPROPERTY(EditDefaultsOnly)
	float _distVisible;
	float _distFromCamera;

	UPROPERTY()
	UExTransformProviderComponent* _exTransformProviderComp;

public:
	UPROPERTY(BlueprintAssignable)
	FDMD_OnActorChanged OnWidgetOwnerChangedDelegate;
};
