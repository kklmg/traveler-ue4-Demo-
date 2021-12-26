// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimNotify/AnimNotifyKey.h"
#include "AnimationEventComponent.generated.h"

class UAnimNotifyHandler;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRAVELER_API UAnimationEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAnimationEventComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void notifyBegin(EAnimNorifyKey notifyKey, float totalTime);
	void notifyTick(EAnimNorifyKey notifyKey, float frameDeltaTime);
	void notifyEnd(EAnimNorifyKey notifyKey);

	UAnimNotifyHandler* GetHNotifyHandler(EAnimNorifyKey notifyKey);

private:
	UPROPERTY()
	TMap<EAnimNorifyKey, UAnimNotifyHandler*> _mapSubscribers;

};


