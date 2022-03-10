// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damage/MyDamageType.h"
#include "DamageHandlerComponent.generated.h"

class UDamageProcessManager;

class IAttributeInterface;
class IActorUIInterface;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UDamageHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageHandlerComponent();

	void HandleDamage(UMyDamageType* damageType);

	UFUNCTION()
	void OnHealthChanged(float preValue,float newValue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	
	UPROPERTY()
	UDamageProcessManager* _damageProcessManager;

	IAttributeInterface* _attributeInterface;
	IActorUIInterface* _actorUIInterface;
};
