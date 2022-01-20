// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/EnumMeshSocketType.h"
#include "Data/EnumAttributeType.h"
#include "Data/EnumCharacterState.h"
#include "Interface/ActionInterface.h"
#include "Interface/AttributeInterface.h"
#include "Interface/StateInterface.h"
#include "CreatureCharacter.generated.h"


class UActionComponent;
class UAttributeComponent;
class UWidgetComponent;
class UBillboardComponent;
class UBillBoardWidgetComponent;
class UAnimationEventComponent;
class UStateComponent;

class AWeapon;
class UActionBase;
class AProjectile;
class UActionBlackBoard;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStateChanged, ECharacterState, characterState);

UCLASS()
class TRAVELER_API ACreatureCharacter : public ACharacter, public IActionInterface, public IAttributeInterface, public IStateInterface
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

	//Attribute Interface implementation---------------------------------------------------

	UFUNCTION(BlueprintCallable)
	virtual UCharacterAttribute* VGetAttribute(EAttributeType attributeType) override;

	UFUNCTION(BlueprintCallable)
	virtual bool VSetAttribute(EAttributeType attributeType, float newValue) override;

	UFUNCTION(BlueprintCallable)
	virtual bool VSetAttributeChange(EAttributeType attributeType, float deltaValue) override;

	//Action Interface implementation ---------------------------------------------------

	UFUNCTION(BlueprintCallable)
	virtual UActionBase* VExecuteAction(EActionType actionType) override;

	UFUNCTION(BlueprintCallable)
	virtual UActionBlackBoard* VGetActionBlackBoard() override;

	//State Interface implementation---------------------------------------------------
	FStateData VGetStateData() override;

	void VSetSituationState(ESituationState newState) override;
	void VSetActionState(EActionState newState) override;
	void VSetHealthState(EHealthState newState) override;
	void VSetPostureState(EPostureState newState) override;

	FOnSituationStateChanged* VGetSituationStateChangedDelegate() override;
	FOnActionStateChanged* VGetActionStateChangedDelegate() override;
	FOnHealthStateChanged* VGetHealthStateChangedDelegate() override;
	FOnPostureStateChanged* VGetPostureStateChangedDelegate() override;
	

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
	UAnimationEventComponent* GetAnimationEventComponent();

protected:
	UPROPERTY(VisibleAnywhere)
	UActionComponent* _actionComponent;

	UPROPERTY(VisibleAnywhere)
	UStateComponent* _stateComponent;

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
