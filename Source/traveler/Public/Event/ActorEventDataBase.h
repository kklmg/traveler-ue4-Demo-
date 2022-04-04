// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Event/EventDataBase.h"
#include "ActorEventDataBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActorEventDataBase : public UEventDataBase
{
	GENERATED_BODY()
public:
	void SetActor(AActor* actor);
	AActor* GetActor();
private:
	AActor* _actor;
};
