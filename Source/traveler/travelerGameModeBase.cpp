// Copyright Epic Games, Inc. All Rights Reserved.


#include "travelerGameModeBase.h"

void AtravelerGameModeBase::StartPlay() 
{
	Super::StartPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "AtravelerGameModeBase::StartPlay");
}