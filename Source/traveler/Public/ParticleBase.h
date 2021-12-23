// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticleBase.generated.h"

class UNiagaraComponent;

UCLASS()
class TRAVELER_API AParticleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//ANiagaraActor


private:
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* _nigaraComponent;
};
