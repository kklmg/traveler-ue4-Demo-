// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/EnumMeshSocketType.h"
#include "Data/EnumAttributeType.h"
#include "Data/EnumCharacterState.h"
#include "Interface/AnimationModelProvider.h"
#include "Interface/ActionInterface.h"
#include "Interface/AttributeInterface.h"
#include "Interface/StateInterface.h"
#include "Interface/CharacterCameraInterface.h"
#include "Interface/WeaponInterface.h"
#include "Interface/MeshSocketTransformProvider.h"
#include "CreatureCharacter.generated.h"


class UActionComponent;
class UAttributeComponent;
class UWidgetComponent;
class UBillboardComponent;
class UBillBoardWidgetComponent;
class UAnimationEventComponent;
class UInputHandlerComponent;
class UStateComponent;
class UPawnCameraComponent;
class UCameraSpringArmComponent;
class UWeaponComponent;
class UMeshSocketComponent;


class AWeaponBase;
class UActionBase;
class AProjectile;
class UActionBlackBoard;


UCLASS()
class TRAVELER_API ACreatureCharacter : public ACharacter, public IActionInterface, public IAttributeInterface,public IStateInterface, 
										public ICharacterCameraInterface,public IWeaponInterface,public IAnimationModelProvider,public IMeshSocketTransformProvider
{
	GENERATED_BODY()

public:
	ACreatureCharacter(const FObjectInitializer& ObjectInitializer);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	virtual void VSetSituationState(ESituationState newState) override;
	virtual void VSetHealthState(EHealthState newState) override;
	virtual void VSetPostureState(EPostureState newState) override;
	UFUNCTION(BlueprintCallable)
	virtual void VSetAnimationState(EAnimationState newState);
	UFUNCTION(BlueprintCallable)
	virtual EAnimationState VGetAnimationState();

	virtual FOnSituationStateChanged* VGetSituationStateChangedDelegate() override;
	virtual FOnHealthStateChanged* VGetHealthStateChangedDelegate() override;
	virtual FOnPostureStateChanged* VGetPostureStateChangedDelegate() override;
	virtual FOnAnyStateChanged* VGetAnyStateChangedDelegate() override;
	virtual FOnAnimationStateChanged* VGetAnimationStateChangedDelegate() override;

	//Character Camera Interface implementation---------------------------------------------------
	virtual void VCameraArmPitch(float angle)  override;
	virtual void VCameraArmYaw(float angle)   override;
	virtual void VCameraZoomInOut(float offset)  override;
	virtual FRotator VGetCameraRotation() override;
	virtual FVector VGetCameraLocation() override;
	virtual	void VDragCamera(FVector offset) override;
	virtual	void VCancelDragCamera() override;
	virtual	void VSetCameraArmPitchLimit(float pitchMin, float pitchMax) override;
	virtual	void VResetCameraArmPitchLimit() override;
	virtual float VGetCameraArmLength() override;
	virtual UCameraComponent* VGetCameraComponent() override;


	//Weapon Interface implementation---------------------------------------------------
	virtual void VEquipWeapon(AWeaponBase* weapon) override;
	virtual AWeaponBase* VGetEquipedWeapon() override;
	virtual void VStartFiring() override;
	virtual void VStopFiring() override;
	virtual void VStartAiming() override;
	virtual void VStopAiming() override;


	//AnimationModel Provider Interface implementation --------------------------------------------------
	virtual FAnimationModel VGetAnimationModel() override;
	virtual FAnimationModel& VGetAnimationModelRef() override;


	//MeshSocketTransform Provider Interface implementation --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	virtual bool VTryGetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform) override;

	UFUNCTION(BlueprintCallable)
	FName GetMeshSocketNameByType(EMeshSocketType meshSocketType);

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
	UInputHandlerComponent* _inputHandlerComponent;

	UPROPERTY(VisibleAnywhere)
	UPawnCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraSpringArmComponent* _cameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* _weaponComponent;

	UPROPERTY(VisibleAnywhere)
	UMeshSocketComponent* _meshSocketComponent;

	UPROPERTY()
	FAnimationModel _animationModel;
};
