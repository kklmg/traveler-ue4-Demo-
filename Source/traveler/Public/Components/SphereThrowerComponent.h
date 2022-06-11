// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/ThrowerInterface.h"
#include "Data/ThrowerData.h"
#include "SphereThrowerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API USphereThrowerComponent : public UActorComponent, public IThrowerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USphereThrowerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void VSetSpawningLocation(FVector location) override;
	virtual void VSetSpawningActorScale(float scale) override;
	virtual void VSetThrowingDirection(FVector direction) override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;
	virtual void VStartThrowing() override;
	virtual void VStopThrowing() override;

private:
	void SphereTracing();

	UPROPERTY(EditDefaultsOnly)
	float _tracingInterval;

	FThrowerData _throwerData;
	float _elapsedTime;
	float _elapsedTimeFromLastTracing;
	bool _bIsThrowing;
};
