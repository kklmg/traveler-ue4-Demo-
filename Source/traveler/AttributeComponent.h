// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


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

private:
	UPROPERTY(Category = Attribute, EditAnyWhere)
	float _velocity;
	UPROPERTY(Category = Attribute, EditAnyWhere)
	float _health;
	UPROPERTY(Category = Attribute, EditAnyWhere)
	float _strength;
	UPROPERTY(Category = Attribute, EditAnyWhere)
	float _energy;
public:
	float GetVelocity();
};
