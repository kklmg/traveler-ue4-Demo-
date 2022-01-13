// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ThrowerActorBase.h"
#include "Components/SceneComponent.h"
#include "Data/ThrowerData.h"
#include "ThrowerActor.generated.h"

class UCurveFloat;
class USceneComponent;
class UThrowerComponent;


UCLASS()
class TRAVELER_API AThrowerActor : public AThrowerActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void VSetSpawningActorScale(float scale) override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;
	virtual FThrowerData VGetThrowerData() override;
	virtual void VAutoDestroy() override;


protected: 
	UPROPERTY(EditDefaultsOnly, Category = ThrowerSetting)
	FThrowerData _throwerData;
private:
	UPROPERTY(VisibleAnywhere, Category = components)
	USceneComponent* _rootComp;

	UPROPERTY(VisibleAnywhere, Category = components)
	UThrowerComponent* _throwerComp;
};
