// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, AActor*, Actor, float, NewValue, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Attributes)
	float _health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Attributes)
	float _healthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Attributes)
	float _mana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = Attributes)
	float _manaMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	float _walkSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	float _runSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	float _strength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	float _level;
public:
	UPROPERTY(BlueprintAssignable, Category = Attributes)
	FOnAttributeChanged OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = Attributes)
	FOnAttributeChanged OnManaChangedDelegate;

public:
	UFUNCTION(BlueprintCallable)
	void SetHealth(float newValue);
	UFUNCTION(BlueprintCallable)
	void SetHealMax(float newValue);
	UFUNCTION(BlueprintCallable)
	void SetMana(float newValue);
	UFUNCTION(BlueprintCallable)
	void SetManaMax(float newValue);

public:
	float GetWalkSpeed();
	float GetRunSpeed();
};
