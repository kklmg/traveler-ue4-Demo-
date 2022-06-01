// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interface_PostProcessVolume.h"
#include "PostProcessActor.generated.h"

class UPostProcessComponent;

UCLASS()
class TRAVELER_API APostProcessActor : public AActor, public IInterface_PostProcessVolume
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APostProcessActor();

	void SetIsActive(bool bActive);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool EncompassesPoint(FVector Point, float SphereRadius/*=0.f*/, float* OutDistanceToPoint) override;
	virtual FPostProcessVolumeProperties GetProperties()const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	UPostProcessComponent* _postProcessComp;
};
