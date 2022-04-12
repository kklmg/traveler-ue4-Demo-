// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "UI/ActorWidget.h"
#include "Data/ActorUIData.h"
#include "Data/CombatData.h"
#include "ActorUIComponent.generated.h"


class UUserWidget;
/**
 * 
 */
UCLASS()
class TRAVELER_API UActorUIComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActorUIComponent();
protected:

	virtual void InitializeComponent() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShowActorUI(EActorUI widgeType);
	void HideActorUI(EActorUI widgeType);
	void ShowActorStatusEffectUI(EStatusEffect StatusType, float duration);
	void HideActorStatusEffectUI(EStatusEffect StatusType);

private:

	UPROPERTY(EditDefaultsOnly)
	bool _bShowStatusDefault;

	UPROPERTY(EditDefaultsOnly)
	TMap<EActorUI,FActorUIData> _mapWidgetClass;

	UPROPERTY()
	TMap<EActorUI, UActorWidget*> _mapWidgetInstance;

	UPROPERTY()
	UActorWidget* _widget;
};
