// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"
#include "Data/CharacterAttribute.h"
#include "Data/AttributeData.h"
#include "Net/UnrealNetwork.h"
#include "Engine/DataTable.h"


// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	_health = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::Health);
	_health->Initialize(AttributeName::Health,90, 0, 100);
	_mapAttributes.Add(_health->GetName(),_health);

	_mana = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::Mana);
	_mana->Initialize(AttributeName::Mana, 90, 0, 100);
	_mapAttributes.Add(_mana->GetName(), _mana);

	_energy = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::Energy);
	_energy->Initialize(AttributeName::Energy, 90, 0, 100);
	_mapAttributes.Add(_energy->GetName(), _energy);

	_level = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::Level);
	_level->Initialize(AttributeName::Level, 90, 0, 100);
	_mapAttributes.Add(_level->GetName(), _level);

	_walkingSpeed = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::WalkingSpeed);
	_walkingSpeed->Initialize(AttributeName::WalkingSpeed, 90, 0, 100);
	_mapAttributes.Add(_walkingSpeed->GetName(), _walkingSpeed);

	_runningSpeed = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::RuningSpeed);
	_runningSpeed->Initialize(AttributeName::RuningSpeed, 90, 0, 100);
	_mapAttributes.Add(_runningSpeed->GetName(), _runningSpeed);

	_strength = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::Strength);
	_strength->Initialize(AttributeName::Strength, 90, 0, 100);
	_mapAttributes.Add(_strength->GetName(), _strength);

}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitializeAttributes();
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//
UCharacterAttribute* UAttributeComponent::GetAttribute(FName name)
{
	if (_mapAttributes.Contains(name)) 
	{
		return _mapAttributes[name];
	}
	return nullptr;
}

void UAttributeComponent::InitializeAttributes()
{
	FString contextString;
	TArray<FAttributeRow*> rows;
	_attributeTable->GetAllRows<FAttributeRow>(contextString, rows);


	FAttributeRow** row = rows.FindByPredicate([](const FAttributeRow* attribute) {return attribute->Level == 1; });

	if (row) 
	{
		(*row)->Level;
	}


	for(TSubclassOf<UCharacterAttribute> attributeClass: _ArrayAttributeClasses)
	{
		UCharacterAttribute* attribute = NewObject<UCharacterAttribute>(this, attributeClass);

		if (_mapAttributes.Contains(attribute->GetName()))
		{
			UE_LOG(LogTemp, Warning, TEXT("trying add duplicated attribute"));
		}
		else
		{
			_mapAttributes.Add(attribute->GetName(), attribute);
		}
	}
}

void UAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAttributeComponent, _health);
	DOREPLIFETIME(UAttributeComponent, _mana);
	DOREPLIFETIME(UAttributeComponent, _energy);
}

