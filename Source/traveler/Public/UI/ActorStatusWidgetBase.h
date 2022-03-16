// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Process/CompositeProcessBase.h"
#include "ActorStatusWidgetBase.generated.h"


UENUM(/*BlueprintType,*/ meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EActorStatusUI/* : uint8*/
{
	EAStatus_NONE = 0 UMETA(Hidden),
	EAStatus_Level = 1 << 0 UMETA(DisplayName = "Level"),
	EAStatus_Health = 1 << 1 UMETA(DisplayName = "Health"),
	EAStatus_Mana = 1 << 2 UMETA(DisplayName = "Mana"),
	EAStatus_Stamina = 1 << 3 UMETA(DisplayName = "Stamina"),
	EAStatus_Energy = 1 << 4 UMETA(DisplayName = "Energy"),
	EAStatus_Fire = 1 << 5 UMETA(DisplayName = "Fire"),
	EAStatus_Water = 1 << 6 UMETA(DisplayName = "Water"),
	EAStatus_Ice = 1 << 7 UMETA(DisplayName = "Ice"),
	EAStatus_Electricity = 1 << 8 UMETA(DisplayName = "Electricity"),
	EAStatus_Poision = 1 << 9 UMETA(DisplayName = "Poision"),
	EAStatus_Stun = 1 << 10 UMETA(DisplayName = "Stun"),
};
ENUM_CLASS_FLAGS(EActorStatusUI);

class UPanelWidget;
class UFlickeringWidget;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActorStatusWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetData();

	void ShowStatus(EActorStatusUI actorStatus, float duration);
	void HideStatus(EActorStatusUI actorStatus, float duration);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	UPROPERTY(EditAnyWhere, meta = (bindwidget))
	UPanelWidget* statusHolder;

	UPROPERTY(EditAnyWhere)
	TMap<EActorStatusUI, TSubclassOf<UFlickeringWidget>> _widgetClassMap;

	UPROPERTY()
	TMap<EActorStatusUI, UFlickeringWidget*> _widgetInsMap; 
};
