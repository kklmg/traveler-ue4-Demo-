// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameSystem/travelerGameModeBase.h"

void AtravelerGameModeBase::StartPlay() 
{
	Super::StartPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "AtravelerGameModeBase::StartPlay");
}