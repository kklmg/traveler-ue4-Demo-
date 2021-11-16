// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UPawnCameraComponent;
class UCameraSpringArmComponent;
class UActionComponent;
class UWeaponComponent;
class UAttributeComponent;

class AWeapon;
class AProjectile;

UENUM(BlueprintType)
enum class EMeshSocketType : uint8
{
	MST_LeftHand UMETA(DisplayName = "LeftHand"),
	MST_RightHand UMETA(DisplayName = "RightHand"),
	MST_LeftHandDraw UMETA(DisplayName = "LeftHandDraw"),
	MST_RightHandDraw UMETA(DisplayName = "RightHandDraw"),
};


UCLASS()
class TRAVELER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	UCameraSpringArmComponent* GetSpringArmComponent();

	UFUNCTION(BlueprintCallable)
	UPawnCameraComponent* GetCameraComponent();

	UFUNCTION(BlueprintCallable)
	UAttributeComponent* GetAttributeComponent();

	UFUNCTION(BlueprintCallable)
	UWeaponComponent* GetWeaponComponent();

	UFUNCTION(BlueprintCallable)
	AWeapon* GetEquippedWeapon();

	UFUNCTION(BlueprintCallable)
	FName GetMeshSocketNameByType(EMeshSocketType meshSocketType);

	UFUNCTION(BlueprintCallable)
	bool GetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace,FTransform& outTransform);

private:
	// FPS camera.
	UPROPERTY(VisibleAnywhere)
	UPawnCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraSpringArmComponent* _cameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UActionComponent* _actionComponent;

	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* _weaponComponent;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* _attributeComponent;

	UPROPERTY(EditDefaultsOnly, Category = Sockets)
	TMap<EMeshSocketType,FName> _socketsMap;
};
