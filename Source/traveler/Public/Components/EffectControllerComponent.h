// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/MyDelegates.h"
#include "Components/ActorComponent.h"
#include "Enums/EnumCombat.h"
#include "Effet/EnumEffect.h"
#include "EffectControllerComponent.generated.h"



class UEffectPlayerBase;




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRAVELER_API UEffectControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectControllerComponent();

	virtual void InitializeComponent() override;

	void PlayEffect(EEffectType effectType, uint8 effectOption);
	void StopEffect(EEffectType effectType, uint8 effectOption);
	FMD_BoolValueChangeSignature* GetEffectFinishedDelegate(EEffectType effectType);

	// Called when the game starts
	virtual void BeginPlay() override;

	void SetupDynamicMaterial(int32 elementIndex);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* _MID;

	UPROPERTY(EditDefaultsOnly)
	TMap<EEffectType, TSubclassOf<UEffectPlayerBase>> _effectPlayerClassMap;

	UPROPERTY()
	TMap<EEffectType, UEffectPlayerBase*> _effectPlayerInsMap;
};
