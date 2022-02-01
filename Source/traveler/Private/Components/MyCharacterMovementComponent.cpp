// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"
#include "Interface/AttributeInterface.h"
#include "Interface/ActionInterface.h"
#include "Interface/AnimationModelProvider.h"

void UMyCharacterMovementComponent::BeginPlay()
{
	_actionInterface = GetOwner<IActionInterface>();
	_attributeInterface = GetOwner<IAttributeInterface>();
	_animationModelProviderInterface = GetOwner<IAnimationModelProvider>();
	

	if(_attributeInterface && _actionInterface)
	{
		//set walking speed 
		UCharacterAttribute* WalkingSpeed = _attributeInterface->VGetAttribute(EAttributeType::EATT_WalkingSpeed);
		if (WalkingSpeed)
		{
			MaxWalkSpeed = WalkingSpeed->GetValue();
		}

		_actionInterface->VGetActionBlackBoard()->
			GetValueChangedDelegate_Bool(EActionDataKey::EACTD_WantToSprint).AddUFunction(this, FName(TEXT("OnCharacterWantToSprint")));
	}
}

void UMyCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_animationModelProviderInterface)
	{
		FAnimationModel& model = _animationModelProviderInterface->VGetAnimationModelRef();
		model.MovingVelocity = Velocity;
		model.MovementMode = MovementMode;
	}
}

void UMyCharacterMovementComponent::OnCharacterWantToSprint(bool wantToSprint)
{
	if (_attributeInterface)
	{
		if (wantToSprint)
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
