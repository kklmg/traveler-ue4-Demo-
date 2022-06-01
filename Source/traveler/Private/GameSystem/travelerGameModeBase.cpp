// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameSystem/travelerGameModeBase.h"
#include "GameSystem/PostProcessControlBase.h"

AtravelerGameModeBase::AtravelerGameModeBase()
{
	PostProcessControlClass = APostProcessControlBase::StaticClass();
}

FORCEINLINE_DEBUGGABLE APostProcessControlBase* AtravelerGameModeBase::GetPostProcessControl()
{
	return _postProcessControlIns;
}

void AtravelerGameModeBase::StartPlay()
{
	Super::StartPlay();

	_postProcessControlIns = GetWorld()->SpawnActor<APostProcessControlBase>(PostProcessControlClass);
	check(_postProcessControlIns);
}