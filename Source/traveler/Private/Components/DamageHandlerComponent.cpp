// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageHandlerComponent.h"
#include "Damage/StatusEffectProcessManager.h"
#include "Interface/StatusInterface.h"
#include "Interface/ActorUIInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Damage/DamageDisplayer.h"
#include "UI/MyHUD.h"

// Sets default values for this component's properties
UDamageHandlerComponent::UDamageHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UDamageHandlerComponent::HandleDamage(float basicDamage, EDamageType damageType, FVector impactPoint, AActor* causer)
{
	float finalDamage = CalculateDamage(basicDamage, damageType, causer, GetOwner());

	//apply damage
	if (_statusInterface) 
	{
		_statusInterface->VApplyRemainingValueChange(EStatusType::EStatus_Health, -finalDamage);
	}

	//show damage om screen
	if(_hud)
	{
		FDamageDisplayData damageDisplayData;
		damageDisplayData.Damage = finalDamage;
		damageDisplayData.DamageType = damageType;
		damageDisplayData.Location = impactPoint;

		_hud->ShowDamage(damageDisplayData);
	}
}

void UDamageHandlerComponent::HandleDamage(UMyDamageType* damageType, FVector impactPoint, AActor* causer)
{
	if (!_StatusEffectProcessManager) return;
	if (!damageType) return;

	//handle basic damage
	HandleDamage(damageType->Damage, damageType->DamageType, impactPoint, causer);

	//AActor* owner = GetOwner();
	//UGameplayStatics::ApplyDamage(owner,damageType->Damage, owner);
	// 
	//handle status effect
	if (damageType->StatusEffectDataClass)
	{
		UStatusEffectData* statusEffectDataIns = NewObject<UStatusEffectData>(this, damageType->StatusEffectDataClass);
		HandleStatusEffect(statusEffectDataIns, impactPoint, causer);
	}

	//show status UI
	if (_actorUIInterface)
	{
		_actorUIInterface->VShowActorUI(EActorUI::ActorUI_Status);
	}
}

void UDamageHandlerComponent::HandleStatusEffect(UStatusEffectData* statusEffectData, FVector impactPoint, AActor* causer)
{
	_StatusEffectProcessManager->ExecuteProcess(GetOwner(), causer, statusEffectData);
}

void UDamageHandlerComponent::OnHealthChanged(float preValue, float newValue)
{
	
}

// Called when the game starts
void UDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_StatusEffectProcessManager = NewObject<UStatusEffectProcessManager>(this);
	_statusInterface = Cast<IStatusInterface>(GetOwner());
	_actorUIInterface = Cast<IActorUIInterface>(GetOwner());
	_hud = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

//todo
float UDamageHandlerComponent::CalculateDamage(float basicDamage, EDamageType damageType, AActor* damageGiver, AActor* damageReceiver)
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

