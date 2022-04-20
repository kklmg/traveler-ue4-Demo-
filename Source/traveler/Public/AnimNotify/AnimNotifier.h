// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AnimNotifier.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimNotifyBegin, float ,TotalDuration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimNotifyTick, float , FrameDeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimNotifyEnd);

/**
 * 
 */
UCLASS()
class TRAVELER_API UAnimNotifier : public UObject
{
	GENERATED_BODY()
public:
	FOnAnimNotifyBegin NotifyBeginDelegate;
	FOnAnimNotifyTick NotifyTickDelegate;
	FOnAnimNotifyEnd NotifyEndDelegate;
};
