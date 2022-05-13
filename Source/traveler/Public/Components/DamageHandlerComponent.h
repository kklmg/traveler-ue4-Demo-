// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/EnumCombat.h"
#include "Damage/DamageData.h"
#include "DamageHandlerComponent.generated.h"

class UStatusEffectProcessManager;

class UActionComponent;
class UEventBrokerComponent;
class UActorUIComponent;
class UStatusComponent;

class UDamageData;
class UStatusEffectData;

class AMyHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UDamageHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageHandlerComponent();

	bool IsDamageable();
	void HandleDamage(float basicDamage, EElementalType elementalType, FVector impactPoint, AActor* causer, APawn* instigator, bool bForce = false);
	void HandleDamageData(FDamageData& damageData, FVector impactPoint, AActor* causer, APawn* instigator, bool bForce = false);
	void HandleStatusEffect(UStatusEffectData* statusEffectData, FVector impactPoint, AActor* causer, APawn* instigator, bool bForce = false);


protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	float CalculateDamage(float basicDamage, EElementalType damageType, AActor* damageReceiver, AActor* causer, APawn* instigator);
	void OnReceiveEvent_LifeStateChanged(UObject* eventBaseData);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY()
	UStatusEffectProcessManager* _StatusEffectProcessManager;

	UPROPERTY()
	AMyHUD* _hud;

	UPROPERTY()
	UActorUIComponent* _actorUIComp;

	UPROPERTY()
	UStatusComponent* _statusComp;

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY()
	UEventBrokerComponent* _eventBrokerComp;

	bool _bIsActorAlive;
};
