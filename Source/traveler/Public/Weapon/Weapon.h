// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AMyCharacter;
class UPoseableMeshComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_UnKnown UMETA(DisplayName = "UnKnown"),
	WT_Sword UMETA(DisplayName = "Sword"),
	WT_DualSword UMETA(DisplayName = "DualSword"),
	WT_Knife UMETA(DisplayName = "Knife"),
	WT_Bow UMETA(DisplayName = "Bow"),
};

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
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _skeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	AMyCharacter* _weaponOwner;

	bool _isReadyToFire;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EWeaponType WeaponType;


public:
	/**/
	virtual void OnFireButtonDown() PURE_VIRTUAL(AWeapon::OnFireButtonDown.;);
	virtual void OnFireButtonPress(float deltaTime);
	virtual void OnFireButtonUp();

	virtual void OnAimButtonDown();
	virtual void OnAimButtonPress(float deltaTime);
	virtual void OnAimButtonUp();

	virtual void OnEnterAnimFrame_ReloadStart();
	virtual void OnTickAnimFrame_Reloading();
	virtual void OnEnterAnimFrame_ReloadCompleted();

	virtual FTransform GetMuzzleTransform();

	virtual void OnEnterAnimFrame_Launch();

public:
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMeshComponent();


	UFUNCTION(BlueprintCallable)
	AMyCharacter* GetWeaponOwner();

	UFUNCTION(BlueprintCallable)
	void SetIsReadyToFire(bool fireable);

	UFUNCTION(BlueprintCallable)
	bool IsReadyToFire();
};