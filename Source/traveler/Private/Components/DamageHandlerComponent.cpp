// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DamageHandlerComponent.h"
#include "Damage/DamageProcessManager.h"
#include "Damage/DamageProcessBase.h"
#include "Interface/AttributeInterface.h"
#include "Interface/ActorUIInterface.h"
#include "Kismet/GameplayStatics.h"

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
	damageProcess->SetData(GetOwner(), damageType, _hud);

	_damageProcessManager->ExecuteProcess(damageProcess);
}

void UDamageHandlerComponent::OnHealthChanged(float preValue, float newValue)
{
	if(_actorUIInterface)
	{
		_actorUIInterface->VShowWidget(EWidgetType::WT_HealthBar);
	}

	GetWorld()->GetGameInstance();
}

// Called when the game starts
void UDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_damageProcessManager = NewObject<UDamageProcessManager>(this);
	_attributeInterface = Cast<IAttributeInterface>(GetOwner());
	_actorUIInterface = Cast<IActorUIInterface>(GetOwner());

	if(_attributeInterface)
	{
		UCharacterAttribute* attHealth = _attributeInterface->VGetAttribute(EAttributeType::EATT_Health);
		if(attHealth)
		{
			attHealth->onValueChanged.AddDynamic(this, &UDamageHandlerComponent::OnHealthChanged);
		}
	}

	_hud = Cast<AMyHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

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

