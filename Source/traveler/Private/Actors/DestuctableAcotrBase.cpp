// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DestuctableAcotrBase.h"
#include "Components/LifeControlComponent.h"
#include "Condition/CompositeActorCondition.h"
#include "Components/EventBrokerComponent.h"
#include "Components/ActorUIComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Components/EffectControllerComponent.h"
#include "Components/DamageHandlerComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Components/StatusComponent.h"
#include "Components/LifeControlComponent.h"

// Sets default values
ADestuctableAcotrBase::ADestuctableAcotrBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Event Broker component
	if (_eventBrokerComponent == nullptr)
	{
		_eventBrokerComponent = CreateDefaultSubobject<UEventBrokerComponent>(TEXT("EventBrokerComponent"));
		check(_eventBrokerComponent != nullptr);
	}

	//life Control component
	if (_lifeControlComponent == nullptr)
	{
		_lifeControlComponent = CreateDefaultSubobject<ULifeControlComponent>(TEXT("LifeControlComponent"));
		check(_lifeControlComponent != nullptr);
	}

	//Static Mesh component
	if (_meshComponent == nullptr)
	{
		_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
		check(_meshComponent != nullptr);
		SetRootComponent(_meshComponent);
	}

	//Create Stauts component
	if (_statusComponent == nullptr)
	{
		_statusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
		check(_statusComponent != nullptr);
	}

	//Create Extra Transform provider component
	if (_ExTransformProviderComp == nullptr)
	{
		_ExTransformProviderComp = CreateDefaultSubobject<UExTransformProviderComponent>(TEXT("ExTransformProviderComponent"));
		check(_ExTransformProviderComp != nullptr);
		_ExTransformProviderComp->Initialize(_meshComponent);
	}

	//Create ActorUIComponent component
	if (_actorUIComponent == nullptr)
	{
		_actorUIComponent = CreateDefaultSubobject<UActorUIComponent>(TEXT("ActorUIComponent"));
		check(_actorUIComponent != nullptr);
	}

	//Damage Handler component
	if (_damageHandlerComponent == nullptr)
	{
		_damageHandlerComponent = CreateDefaultSubobject<UDamageHandlerComponent>(TEXT("DamageHandlerComponent"));
		check(_damageHandlerComponent != nullptr);
	}

	//effect controller
	if (_effectControllerComponent == nullptr)
	{
		_effectControllerComponent = CreateDefaultSubobject<UEffectControllerComponent>(TEXT("EffectControllerComponent"));
		check(_effectControllerComponent);
	}
}

// Called when the game starts or when spawned
void ADestuctableAcotrBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestuctableAcotrBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

