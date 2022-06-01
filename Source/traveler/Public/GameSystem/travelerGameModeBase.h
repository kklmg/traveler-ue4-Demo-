// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "travelerGameModeBase.generated.h"

class APostProcessControlBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API AtravelerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AtravelerGameModeBase();

	APostProcessControlBase* GetPostProcessControl();

private:
	void StartPlay() override;

	UPROPERTY(EditAnywhere, Category = Classes)
	TSubclassOf<APostProcessControlBase> PostProcessControlClass;

	UPROPERTY()
	APostProcessControlBase* _postProcessControlIns;
};
