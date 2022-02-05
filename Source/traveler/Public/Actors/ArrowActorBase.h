// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ProjectileActorBase.h"
#include "ArrowActorBase.generated.h"



UENUM(BlueprintType)
enum class EArrowState : uint8
{
	EAS_None UMETA(DisplayName = "None"),
	EAS_Spawned UMETA(DisplayName = "Spawned"),
	EAS_Launched UMETA(DisplayName = "Launched"),
	EAS_Hitted UMETA(DisplayName = "Hitted"),
};


/**
 * 
 */
UCLASS()
class TRAVELER_API AArrowActorBase : public AProjectileActorBase
{
	GENERATED_BODY()
public:
	AArrowActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Launch();
	void SetLaunchDirection(FVector direction);

private:
	UPROPERTY(VisibleAnywhere)
	FVector _launchDirection;

	UPROPERTY(VisibleAnywhere)
	float _elapsedTimeFromLaunch;

	UPROPERTY(EditDefaultsOnly)
	float _gravity;

	UPROPERTY(EditDefaultsOnly)
	float _lifeAfterLaunch;

	UPROPERTY(EditDefaultsOnly)
	float _timeToDrop;

	UPROPERTY(VisibleAnywhere)
	EArrowState _arrowState;
};
