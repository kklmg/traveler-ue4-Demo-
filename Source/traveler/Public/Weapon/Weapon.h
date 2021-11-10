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
	void Initialize(AMyCharacter* weaponOwner);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

	AMyCharacter* _weaponOwner;

	bool _isReadyToFire;

public:
	/**/
	virtual void OnFireStart() PURE_VIRTUAL(AWeapon::OnFireStart.;);
	virtual void FiringInProgress(float deltaTime);
	virtual void OnFireEnd();

	virtual void OnAimStart();
	virtual void AimmingInProgress(float deltaTime);
	virtual void OnAimEnd();

	virtual void OnAnimFrameStart_Fire();
public:
	UFUNCTION(BlueprintCallable)
	AMyCharacter* GetWeaponOwner();

	UFUNCTION(BlueprintCallable)
	void SetIsReadyToFire(bool fireable);

	UFUNCTION(BlueprintCallable)
	bool IsReadyToFire();
};