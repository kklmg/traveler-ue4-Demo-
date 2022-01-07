// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/EnumMeshSocketType.h"
#include "Data/EnumAttributeType.h"
#include "Interface/ActionInterface.h"
#include "CreatureCharacter.generated.h"


class UActionComponent;
class UAttributeComponent;
class UWidgetComponent;
class UBillboardComponent;
class UBillBoardWidgetComponent;
class UAnimationEventComponent;

class AWeapon;
class UActionBase;
class AProjectile;
class UActionBlackBoard;




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
class TRAVELER_API ACreatureCharacter : public ACharacter,public IActionInterface
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
	UCharacterAttribute* GetAttribute(EAttributeType attributeType);

	UFUNCTION(BlueprintCallable)
	bool SetAttribute(EAttributeType attributeType, float newValue);

	UFUNCTION(BlueprintCallable)
	bool SetAttributeChange(EAttributeType attributeType, float deltaValue);


	UFUNCTION(BlueprintCallable)
	UActionBase* VExecuteAction(EActionType actionType) override;

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* VGetActionBlackBoard() override;

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
