// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatureCharacter.generated.h"

class UActionComponent;
class UAttributeComponent;

class AWeapon;
class AProjectile;
class UActionData;

UENUM(BlueprintType)
enum class EMeshSocketType : uint8
{
	MST_LeftHand UMETA(DisplayName = "LeftHand"),
	MST_RightHand UMETA(DisplayName = "RightHand"),
	MST_LeftHandDraw UMETA(DisplayName = "LeftHandDraw"),
	MST_RightHandDraw UMETA(DisplayName = "RightHandDraw"),
};


UCLASS()
class TRAVELER_API ACreatureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreatureCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UFUNCTION(BlueprintCallable)
	UAttributeComponent* GetAttributeComponent();

	UFUNCTION(BlueprintCallable)
	UActionComponent* GetActionComponent();

	UFUNCTION(BlueprintCallable)
	void ExecuteAction(FName actionName);

	UFUNCTION(BlueprintCallable)
	UActionData* GetActionData();

	UFUNCTION(BlueprintCallable)
	FName GetMeshSocketNameByType(EMeshSocketType meshSocketType);

	UFUNCTION(BlueprintCallable)
	bool GetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform);

protected:
	UPROPERTY(VisibleAnywhere)
	UActionComponent* _actionComponent;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* _attributeComponent;

	UPROPERTY(EditDefaultsOnly, Category = Sockets)
	TMap<EMeshSocketType, FName> _socketsMap;
};
