// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ThrowableInterface.h"
#include "ThrowableActor.generated.h"

UCLASS()
class TRAVELER_API AThrowableActor : public AActor, public IThrowableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void VSetThrowingDirection(FVector dir) override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;

};
