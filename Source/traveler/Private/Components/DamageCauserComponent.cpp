// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageCauserComponent.h"
#include "Damage/DamageData.h"
#include "GameSystem/MyGameplayStatics.h"


// Sets default values for this component's properties
UDamageCauserComponent::UDamageCauserComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageCauserComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(_damageDataClass)
	{
		_damageDataIns = NewObject<UDamageData>(this, _damageDataClass);
	}
};


// Called every frame
void UDamageCauserComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageCauserComponent::CauseDamageTo(AActor* damagedActor)
{
	if (!damagedActor) return;
	if (!_damageDataIns) return;

	UMyGameplayStatics::CauseDamage(damagedActor, _damageDataIns, damagedActor->GetActorLocation(), GetOwner(), nullptr);
}

