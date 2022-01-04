// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ThrowableInterface.h"
#include "Interface/PoolableInterface.h"
#include "ThrowableActor.generated.h"

class UProjectileMovementComponent;

DECLARE_DELEGATE_OneParam(FOnActorInactivated, int)

UCLASS()
class TRAVELER_API AThrowableActor : public AActor, public IThrowableInterface, public IPoolableInterface
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

	virtual void VSetDirection(FVector dir) override;
	virtual void VSetSpeed(float speed) override;
	virtual void VSetLife(float life) override;

	virtual bool VIsActive() override;
	virtual void VSetIsActive(bool isActive) override;

	virtual int VGetPoolId();
	virtual void VSetPoolId(int poolId);

public:
	FOnActorInactivated OnActorInactivated;

private:
	bool _isActive;
	float _elapsedTime;
	float _life;
	int _poolId;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* _rootSceneComp;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* _projectileMovementComp;
};
