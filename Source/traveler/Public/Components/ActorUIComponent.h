// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ActorWidget.h"
#include "Data/ActorUIData.h"
#include "Enums/EnumCombat.h"
#include "ActorUIComponent.generated.h"

class UUserWidget;
class UEventBrokerComponent;


/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRAVELER_API UActorUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActorUIComponent();
protected:

	virtual void InitializeComponent() override;
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShowActorUI(EActorUI widgeType);
	void HideActorUI(EActorUI widgeType);
	void HideAllUI();
	void RemoveAllUI();
	void ShowActorStatusEffectUI(EStatusEffect StatusType, float duration);
	void HideActorStatusEffectUI(EStatusEffect StatusType);

	void OnReceiveEvent_LifeStateChanged(UObject* baseData);
private:

	UPROPERTY(EditDefaultsOnly)
	bool _bShowStatusDefault;

	UPROPERTY(EditDefaultsOnly)
	TMap<EActorUI,FActorUIData> _mapWidgetClass;

	UPROPERTY()
	TMap<EActorUI, UActorWidget*> _mapWidgetInstance;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;
};
