// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageCauserComponent.h"
#include "GameSystem/MyGameplayStatics.h"


// Sets default values for this component's properties
UDamageCauserComponent::UDamageCauserComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_applyDamageRate = 0.5f;
}


// Called when the game starts
void UDamageCauserComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
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

	UMyGameplayStatics::CauseDamage(damagedActor, _damageData, damagedActor->GetActorLocation(), GetOwner(), nullptr);
}

void UDamageCauserComponent::CauseContinousDamageTo(AActor* damagedActor)
{
	UMyGameplayStatics::CauseDamage(damagedActor, _damageData, damagedActor->GetActorLocation(), GetOwner(), nullptr);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle,
		FTimerDelegate::CreateLambda([this, damagedActor]
	{
		if (damagedActor)
		{
			UMyGameplayStatics::CauseDamage(damagedActor, _damageData, damagedActor->GetActorLocation(), GetOwner(), nullptr);
		}
	}), _applyDamageRate, true);
	_damageTimerHandlers.Add(damagedActor, timerHandle);
}

void UDamageCauserComponent::StopContinousDamage(AActor* actor)
{
	if (_damageTimerHandlers.Contains(actor))
	{
		if (_damageTimerHandlers[actor].IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(_damageTimerHandlers[actor]);
			_damageTimerHandlers[actor].Invalidate();
		}
		_damageTimerHandlers.Remove(actor);
	}
}





