// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Damage/DamageDisplayer.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API AMyHUD : public AHUD
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowDamage(FDamageDisplayData damageDisplayData);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageDisplayer> _damageDisplayerClass;
	
	UPROPERTY()
	UDamageDisplayer* _damageDisplayerIns;
};
