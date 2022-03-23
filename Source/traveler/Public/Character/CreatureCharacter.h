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
#include "Damage/DamageHandlerInterface.h"
#include "Interface/ActorUIInterface.h"
#include "CreatureCharacter.generated.h"


class UActionComponent;
class UAttributeComponent;
class UWidgetComponent;
class UBillboardComponent;
class UActorUIComponent;
class UAnimationEventComponent;
class UInputHandlerComponent;
class UStateComponent;
class UPawnCameraComponent;
class UCameraSpringArmComponent;
class UWeaponComponent;
class UMeshSocketComponent;
class UDamageHandlerComponent;
class UIKComponent;


class AWeaponBase;
class UActionBase;
class AProjectile;
class UActionBlackBoard;


UCLASS()
class TRAVELER_API ACreatureCharacter : public ACharacter, public IActionInterface, public IAttributeInterface,public IStateInterface, 
										public ICharacterCameraInterface,public IWeaponInterface,public IAnimationModelProvider,
										public IMeshSocketTransformProvider, public IDamageHandlerInterface, public IActorUIInterface
{
	GENERATED_BODY()

public:
	ACreatureCharacter(const FObjectInitializer& ObjectInitializer);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;

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

	UFUNCTION(BlueprintCallable)
	virtual bool VCanConsume(UCostData* cost) override;

	UFUNCTION(BlueprintCallable)
	virtual bool VTryConsume(UCostData * cost) override;

	//Action Interface implementation ---------------------------------------------------

	UFUNCTION(BlueprintCallable)
	virtual UActionBase* VExecuteAction(EActionType actionType) override;

	UFUNCTION(BlueprintCallable)
	virtual UActionBlackBoard* VGetActionBlackBoard() override;

	UFUNCTION(BlueprintCallable)
	bool VCheckActionIsInProgress(EActionType actionType) override;

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
	virtual void VExecuteWeaponProcess(FName weaponProcessName) override;
	virtual void VStopWeaponProcess(FName weaponProcessName) override;
	virtual void VStopAllProcess() override;


	//AnimationModel Provider Interface implementation --------------------------------------------------
	virtual UAnimationModelBase* VGetAnimationModel() override;


	//Damage Handler Interface implementation --------------------------------------------------
	virtual void VHandleDamage(UMyDamageType* damageType, FHitResult hitResult) override;
	virtual void VHandleStatusEffect(UStatusEffectData* statusEffectData, FHitResult hitResult) override;


	//Actor UI Interface implementation --------------------------------------------------
	virtual void VShowActorUI(EActorUI UIType) override;
	virtual void VHideActorUI(EActorUI UIType) override;
	virtual void VShowActorStatusUI(EStatusEffect StatusType, float duration) override;
	virtual void VHideActorStatusUI(EStatusEffect StatusType) override;


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
	UActorUIComponent* _actorUIComponent;

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

	UPROPERTY(VisibleAnywhere)
	UDamageHandlerComponent* _damageHandlerComponent;

	UPROPERTY(VisibleAnywhere)
	UIKComponent* _IKComponent;

	UPROPERTY()
	UAnimationModelBase* _animationModelIns;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAnimationModelBase> _animationModelClass;
};
