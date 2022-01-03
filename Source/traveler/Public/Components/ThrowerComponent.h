// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowerComponent.generated.h"

class IThrowableInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UThrowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UThrowerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SpawnThrowingActor();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> _spawnActorClass;
	UPROPERTY(EditDefaultsOnly)
	TScriptInterface<IThrowableInterface> _interface;
	UPROPERTY(EditDefaultsOnly)
	FTimerHandle _timerHandle;
	UPROPERTY(EditDefaultsOnly)
	float _throwRate;
	UPROPERTY(EditDefaultsOnly)
	FVector _direction;
	UPROPERTY(EditDefaultsOnly)
	float _life;
	UPROPERTY(EditDefaultsOnly)
	int _poolSize;

	TArray<AActor*> _spawnedActors;
};
