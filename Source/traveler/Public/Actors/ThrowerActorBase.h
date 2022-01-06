// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ThrowerInterface.h"
#include "ThrowerActorBase.generated.h"

UCLASS()
class TRAVELER_API AThrowerActorBase : public AActor,public IThrowerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowerActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
