// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageHandlerComponent.h"
#include "Damage/DamageProcessManager.h"
#include "Damage/DamageProcessBase.h"

// Sets default values for this component's properties
UDamageHandlerComponent::UDamageHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDamageHandlerComponent::HandleDamage(UMyDamageType* damageType)
{
	if (!damageType) return;

	UDamageProcessBase* damageProcess = NewObject<UDamageProcessBase>(this);

	_damageProcessManager->ExecuteProcess(damageProcess);
}

// Called when the game starts
void UDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_damageProcessManager = NewObject<UDamageProcessManager>(this);
	
}


// Called every frame
void UDamageHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(_damageProcessManager)
	{
		_damageProcessManager->Tick(DeltaTime);
	}
}

