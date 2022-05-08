// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageHandlerComponent.h"
#include "Damage/StatusEffectProcessManager.h"
#include "Components/StatusComponent.h"
#include "Components/ActorUIComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Damage/DamageDisplayer.h"
#include "Data/StatusEffectData.h"
#include "UI/MyHUD.h"

// Sets default values for this component's properties
UDamageHandlerComponent::UDamageHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_StatusEffectProcessManager = NewObject<UStatusEffectProcessManager>(this);
	check(_StatusEffectProcessManager);

	_actorUIComp = Cast<UActorUIComponent>(GetOwner()->GetComponentByClass(UActorUIComponent::StaticClass()));
	_statusComp = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	_hud = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

void UDamageHandlerComponent::HandleDamage(float basicDamage, EElementalType elementalType, FVector impactPoint, AActor* causer, APawn* instigator)
{
	float finalDamage = CalculateDamage(basicDamage, elementalType, GetOwner(), causer, instigator);

	//apply damage
	if (_statusComp && finalDamage != 0.0f)
	{
		_statusComp->ApplyRemainingPointChange(EStatusType::EStatus_Health, -finalDamage);
	}

	//show damage om screen
	if (_hud)
	{
		FDamageDisplayData damageDisplayData;
		damageDisplayData.Damage = finalDamage;
		damageDisplayData.ElementalType = elementalType;
		damageDisplayData.Location = impactPoint;

		_hud->ShowDamage(damageDisplayData);
	}
}

void UDamageHandlerComponent::HandleDamageData(FDamageData& damageData, FVector impactPoint, AActor* causer, APawn* instigator)
{
	//handle basic damage
	HandleDamage(damageData.Damage, damageData.ElementalType, impactPoint, causer, instigator);

	//handle status effect
	if (damageData.StatusEffectDataClass)
	{
		UStatusEffectData* statusEffectDataIns = NewObject<UStatusEffectData>(this, damageData.StatusEffectDataClass);
		HandleStatusEffect(statusEffectDataIns, impactPoint, causer, instigator);
	}

	//show status UI
	if (_actorUIComp)
	{
		_actorUIComp->ShowActorUI(EActorUI::ActorUI_Status);
	}

	UGameplayStatics::ApplyDamage(GetOwner(), damageData.Damage, instigator ? instigator->GetController() : nullptr,
		causer, damageData.DamageTypeClass);
}

void UDamageHandlerComponent::HandleStatusEffect(UStatusEffectData* statusEffectData, FVector impactPoint, AActor* causer, APawn* instigator)
{
	if (_StatusEffectProcessManager)
	{
		_StatusEffectProcessManager->ExecuteProcess(GetOwner(), causer, instigator, statusEffectData);
	}
}

void UDamageHandlerComponent::OnHealthChanged(float preValue, float newValue)
{

}

//todo
float UDamageHandlerComponent::CalculateDamage(float basicDamage, EElementalType damageType, AActor* damageReceiver, AActor* causer, APawn* instigator)
{
	return basicDamage;
}


// Called every frame
void UDamageHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(_StatusEffectProcessManager)
	{
		_StatusEffectProcessManager->Tick(DeltaTime);
	}
}

