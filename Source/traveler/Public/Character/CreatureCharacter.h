// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/EnumTransformType.h"
#include "Interface/CharacterCameraInterface.h"
#include "Damage/DamageHandlerInterface.h"
#include "CreatureCharacter.generated.h"


class UActionComponent;
class UAttributeComponent;
class UWidgetComponent;
class UBillboardComponent;
class UActorUIComponent;
class UInputHandlerComponent;
class UStatusComponent;
class UPawnCameraComponent;
class UCameraSpringArmComponent;
class UWeaponComponent;
class UExTransformProviderComponent;
class UDamageHandlerComponent;
class UIKComponent;
class UEffectControllerComponent;
class UAnimControlComponent;
class UEventBrokerComponent;
class ULifeControlComponent;

class AWeaponBase;
class UActionBase;
class AProjectile;
class UActionBlackBoard;

class FDMD_OnFloatValueChanged;


UCLASS()
class TRAVELER_API ACreatureCharacter : public ACharacter , public ICharacterCameraInterface
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


	//Character Camera Interface implementation---------------------------------------------------
	virtual void VCameraArmPitch(float angle)  override;
	virtual void VCameraArmYaw(float angle)   override;
	virtual void VCameraZoomInOut(float offset)  override;
	virtual FQuat VGetCameraRotation() override;
	virtual FVector VGetCameraLocation() override;
	virtual	void VDragCamera(FVector offset) override;
	virtual	void VCancelDragCamera() override;
	virtual	void VSetCameraArmPitchLimit(float pitchMin, float pitchMax) override;
	virtual	void VResetCameraArmPitchLimit() override;
	virtual float VGetCameraArmLength() override;
	virtual UCameraComponent* VGetCameraComponent() override;

protected:
	UPROPERTY(VisibleAnywhere)
	UEventBrokerComponent* _eventBrokerComponent;

	UPROPERTY(VisibleAnywhere)
	UStatusComponent* _statusComponent;

	UPROPERTY(VisibleAnywhere)
	ULifeControlComponent* _lifeControlComponent;

	UPROPERTY(VisibleAnywhere)
	UActionComponent* _actionComponent;

	UPROPERTY(VisibleAnywhere)
	UActorUIComponent* _actorUIComponent;

	UPROPERTY(VisibleAnywhere)
	UInputHandlerComponent* _inputHandlerComponent;

	UPROPERTY(VisibleAnywhere)
	UPawnCameraComponent* _cameraComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraSpringArmComponent* _cameraSpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UWeaponComponent* _weaponComponent;

	UPROPERTY(VisibleAnywhere)
	UExTransformProviderComponent* _ExTransformProviderComp;

	UPROPERTY(VisibleAnywhere)
	UDamageHandlerComponent* _damageHandlerComponent;

	UPROPERTY(VisibleAnywhere)
	UIKComponent* _IKComponent;

	UPROPERTY(VisibleAnywhere)
	UEffectControllerComponent* _effectControllerComponent;

	UPROPERTY(VisibleAnywhere)
	UAnimControlComponent* _animControlComponent;
};
