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

	_level = CreateDefaultSubobject<UCharacterAttribute>(AttributeName::Level);
	_level->Initialize(AttributeName::Level, 2, 0, 100);

	bWantsInitializeComponent = true;
}


void UAttributeComponent::InitializeComponent()
{
	InitializeAttributes();
}

// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
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


bool UAttributeComponent::SetAttribute(FName name,float newValue)
{
	UCharacterAttribute* attribute = GetAttribute(name);
	if (attribute) 
	{
		attribute->SetValue(newValue);
		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeChange(FName name, float deltaValue)
{
	UCharacterAttribute* attribute = GetAttribute(name);
	if (attribute)
	{
		attribute->ApplyValueChange(deltaValue);
		return true;
	}
	return false;
}

void UAttributeComponent::InitializeAttributes()
{
	if (_level)
	{
		_mapAttributes.Add(_level->GetName(), _level);
	}

	if (_attributeTable)
	{
		FString contextString;
		TArray<FAttributeRow*> rows;

		//get all rows from table
		_attributeTable->GetAllRows<FAttributeRow>(contextString, rows);

		for (FAttributeRow* row : rows)
		{
			//Attribute Name is valid,not duplicated
			if (row->Name.IsValid() && _mapAttributes.Contains(row->Name) == false)
			{
				//new instance
				UCharacterAttribute* attribute = NewObject<UCharacterAttribute>(this);

				if (attribute)
				{
					//Initialize
					float LevelMapedValue = _level ? row->GetGrowedValue(_level->GetValue()) : row->value;
					attribute->Initialize(row->Name, LevelMapedValue, 0, LevelMapedValue);

					//Add to attribute map
					_mapAttributes.Add(row->Name, attribute);
				}
			}
		}

	}

	//for(TSubclasrAttribute> atsOf<UCharactetributeClass: _ArrayAttributeClasses)
	//{
	//	UCharacterAttribute* attribute = NewObject<UCharacterAttribute>(this, attributeClass);

	//	if (_mapAttributes.Contains(attribute->GetName()))
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("trying add duplicated attribute"));
	//	}
	//	else
	//	{
	//		_mapAttributes.Add(attribute->GetName(), attribute);
	//	}
	//}
}



//void UAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(UAttributeComponent, _health);
//	DOREPLIFETIME(UAttributeComponent, _mana);
//	DOREPLIFETIME(UAttributeComponent, _energy);
//}

