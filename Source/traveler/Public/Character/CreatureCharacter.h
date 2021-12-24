// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CreatureCharacter.generated.h"

class UActionComponent;
class UAttributeComponent;
class UWidgetComponent;
class UBillboardComponent;
class UBillBoardWidgetComponent;
class UAnimationEventComponent;

class AWeapon;
class UAction;
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

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	CS_GroundNormal UMETA(DisplayName = "GroundNormal"),
	CS_GroundDodging UMETA(DisplayName = "GroundDodging"),
	CS_AirFalling UMETA(DisplayName = "AirFalling"),
	CS_AirNormal UMETA(DisplayName = "AirNormal"),
	CS_AirFlying UMETA(DisplayName = "AirFlying"),
	CS_Swimming UMETA(DisplayName = "Swimming"),
	CS_Stunning UMETA(DisplayName = "Stunning"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStateChanged, ECharacterState, characterState);

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

	//delegates
public:
	FOnCharacterStateChanged OnCharacterStateChangedDelegate;

public:
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	UFUNCTION(BlueprintCallable)
	UCharacterAttribute* GetAttribute(FName name);

	UFUNCTION(BlueprintCallable)
	bool SetAttribute(FName name, float newValue);

	UFUNCTION(BlueprintCallable)
	bool SetAttributeChange(FName name, float deltaValue);


	UFUNCTION(BlueprintCallable)
	UAction* ExecuteAction(FName actionName);

	UFUNCTION(BlueprintCallable)
	UActionData* GetActionData();

	UFUNCTION(BlueprintCallable)
	UBlackboardComponent* GetActionBlackBoard();

	UFUNCTION(BlueprintCallable)
	FName GetMeshSocketNameByType(EMeshSocketType meshSocketType);

	UFUNCTION(BlueprintCallable)
	bool GetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform);

	UFUNCTION()
	void OnCharacterMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	UFUNCTION(BlueprintCallable)
	void SetCharacterState(ECharacterState characterState);

	UFUNCTION(BlueprintCallable)
	ECharacterState GetCharacterState();

	UFUNCTION(BlueprintCallable)
	UActionComponent* GetActionComponent();

	UFUNCTION(BlueprintCallable)
	UAttributeComponent* GetAttributeComponent();

	UFUNCTION(BlueprintCallable)
	UAnimationEventComponent* GetAanimationEventComponent();

protected:
	UPROPERTY(VisibleAnywhere)
	UActionComponent* _actionComponent;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* _attributeComponent;

	UPROPERTY(VisibleAnywhere)
	UBillBoardWidgetComponent* _billboardWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	UAnimationEventComponent* _animationEventComponent;

	UPROPERTY(VisibleAnywhere)
	ECharacterState _characterState;

	UPROPERTY(EditDefaultsOnly, Category = Sockets)
	TMap<EMeshSocketType, FName> _socketsMap;
};
