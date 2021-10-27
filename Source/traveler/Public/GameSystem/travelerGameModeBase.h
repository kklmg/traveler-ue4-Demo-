// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "travelerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API AtravelerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	void StartPlay() override;
};
