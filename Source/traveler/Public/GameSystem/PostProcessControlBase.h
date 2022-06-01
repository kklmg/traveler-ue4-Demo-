// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PostProcessControlBase.generated.h"

class APostProcessActor;

UCLASS()
class TRAVELER_API APostProcessControlBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APostProcessControlBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivateBlurEffect(bool bActive);
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APostProcessActor> _blurEffectActorClass;

	UPROPERTY()
	APostProcessActor* _blurEffectActorIns;
};
