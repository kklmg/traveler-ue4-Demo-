// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AMyCharacter;

UCLASS()
class TRAVELER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void Initialize(AMyCharacter* owner);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

protected:
	AMyCharacter* _owner;

public:
	/**/
	virtual void Fire() PURE_VIRTUAL(AWeapon::Fire.;);
	virtual void FiringInProgress(float deltaTime);
	virtual void OnFireEnd();
};