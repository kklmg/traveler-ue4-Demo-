// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damage/MyDamageType.h"
#include "DamageHandlerComponent.generated.h"

class UStatusEffectProcessManager;

class IAttributeInterface;
class IActorUIInterface;

class AMyHUD;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UDamageHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageHandlerComponent();

	void HandleDamage(float basicDamage, EDamageType damageType, FVector impactPoint, AActor* causer);
	void HandleDamage(UMyDamageType* damageType, FVector impactPoint, AActor* causer);
	void HandleStatusEffect(UStatusEffectData* statusEffectData, FVector impactPoint, AActor* causer);

	UFUNCTION()
	void OnHealthChanged(float preValue,float newValue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float CalculateDamage(float basicDamage, EDamageType damageType, AActor* damageGiver, AActor* damageReceiver);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY()
	UStatusEffectProcessManager* _StatusEffectProcessManager;

	UPROPERTY()
	AMyHUD* _hud;

	IAttributeInterface* _attributeInterface;
	IActorUIInterface* _actorUIInterface;
};
