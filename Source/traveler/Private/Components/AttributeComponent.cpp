// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"
#include "Data/CharacterAttribute.h"
#include "Data/AttributeData.h"
#include "Net/UnrealNetwork.h"
#include "Engine/DataTable.h"
#include "Interface/AnimationModelProvider.h"


// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	_level = CreateDefaultSubobject<UCharacterAttribute>(TEXT("Level"));
	_level->Initialize(EAttributeType::EATT_Level,FText(), 2, 0, 100);

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
UCharacterAttribute* UAttributeComponent::GetAttribute(EAttributeType attributeType)
{
	if (_mapAttributes.Contains(attributeType))
	{
		return _mapAttributes[attributeType];
	}
	return nullptr;
}


bool UAttributeComponent::SetAttribute(EAttributeType attributeType,float newValue)
{
	UCharacterAttribute* attribute = GetAttribute(attributeType);
	if (attribute) 
	{
		attribute->SetValue(newValue);
		return true;
	}
	return false;
}

bool UAttributeComponent::SetAttributeChange(EAttributeType attributeType, float deltaValue)
{
	UCharacterAttribute* attribute = GetAttribute(attributeType);
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
		_mapAttributes.Add(_level->GetAttributeType(), _level);
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
			if (row && _mapAttributes.Contains(row->AttributeType) == false)
			{
				//new instance
				UCharacterAttribute* attribute = NewObject<UCharacterAttribute>(this);

				if (attribute)
				{
					//Initialize
					int level = _level ? _level->GetValue() : 0;
					attribute->Initialize(row, level);

					//Add to attribute map
					_mapAttributes.Add(attribute->GetAttributeType(), attribute);
				}
			}
		}

	}

	//Animation view model setting
	IAnimationModelProvider* animationModelProvider = GetOwner<IAnimationModelProvider>();
	if(animationModelProvider)
	{
		UCharacterAttribute* walkingSpeed = GetAttribute(EAttributeType::EATT_WalkingSpeed);
		if(walkingSpeed)
		{
			animationModelProvider->VGetAnimationModelRef().WalkingSpeed = walkingSpeed->GetValue();
		}
		UCharacterAttribute* sprintSpeed = GetAttribute(EAttributeType::EATT_SprintSpeed);
		if (sprintSpeed)
		{
			animationModelProvider->VGetAnimationModelRef().SprintSpeed = sprintSpeed->GetValue();
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

