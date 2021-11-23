// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_health = 80;
	_healthMax = 100;
	_mana = 80;
	_manaMax = 100;

	_walkSpeed = 600;
	_runSpeed = 1200;
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UAttributeComponent::GetWalkSpeed() 
{
	return _walkSpeed;
}
float UAttributeComponent::GetRunSpeed() 
{
	return _runSpeed;
}

void UAttributeComponent::SetHealth(float newValue)
{
	float deltaValue = newValue - _health;
	_health = FMath::Clamp(newValue, 0.0f, _healthMax);

	OnHealthChangedDelegate.Broadcast(GetOwner(), _health, deltaValue);
}
void UAttributeComponent::SetHealMax(float newValue) 
{
	_healthMax = FMath::Max(1.0f, newValue);
}
void UAttributeComponent::SetMana(float newValue) 
{
	float deltaValue = newValue - _mana;
	_mana = FMath::Clamp(newValue, 0.0f, _manaMax);

	OnManaChangedDelegate.Broadcast(GetOwner(), _mana, deltaValue);
}
void UAttributeComponent::SetManaMax(float newValue) 
{
	_manaMax = FMath::Max(1.0f, newValue);
}


void UAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAttributeComponent, _health);
	DOREPLIFETIME(UAttributeComponent, _healthMax);

	DOREPLIFETIME(UAttributeComponent, _mana);
	DOREPLIFETIME(UAttributeComponent, _manaMax);
}
