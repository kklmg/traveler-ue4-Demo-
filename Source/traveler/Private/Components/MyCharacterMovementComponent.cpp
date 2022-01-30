// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Interface/AttributeInterface.h"
#include "Interface/ActionInterface.h"

void UMyCharacterMovementComponent::BeginPlay()
{
	_actionInterface = GetOwner<IActionInterface>();
	_attributeInterface = GetOwner<IAttributeInterface>();

	if(_attributeInterface && _actionInterface)
	{
		//set walking speed 
		UCharacterAttribute* WalkingSpeed = _attributeInterface->VGetAttribute(EAttributeType::EATT_WalkingSpeed);
		if(WalkingSpeed)
		{
			MaxWalkSpeed = WalkingSpeed->GetValue();
		}
	
		_actionInterface->VGetActionBlackBoard()->
		GetValueChangedDelegate_Bool(EActionDataKey::EACTD_WantToSprint).AddUFunction(this,FName(TEXT("OnCharacterWantToSprint")));
	}
}

void UMyCharacterMovementComponent::OnCharacterWantToSprint(bool wantToSprint)
{
	if (_attributeInterface)
	{
		if(wantToSprint)
		{
			//set to Sprint speed 
			UCharacterAttribute* speed = _attributeInterface->VGetAttribute(EAttributeType::EATT_SprintSpeed);
			if (speed)
			{
				MaxWalkSpeed = speed->GetValue();
			}
		}
		else
		{
			//set to walking speed 
			UCharacterAttribute* speed = _attributeInterface->VGetAttribute(EAttributeType::EATT_WalkingSpeed);
			if (speed)
			{
				MaxWalkSpeed = speed->GetValue();
			}
		}
	}
}
