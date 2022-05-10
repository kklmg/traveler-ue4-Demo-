// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputPresetBase.h"
#include "Input/ButtonInputBase.h"
#include "Input/AxisInputBase.h"
#include "Components/ActionComponent.h"
#include "Components/EventBrokerComponent.h"
#include "Components/WeaponComponent.h"
#include "Interface/CharacterCameraInterface.h"

void UInputPresetBase::VInit(AActor* owner)
{
	check(owner)

	_owner = owner; 
	_actionComp = Cast<UActionComponent>(owner->GetComponentByClass(UActionComponent::StaticClass()));
	_weaponComp = Cast<UWeaponComponent>(owner->GetComponentByClass(UWeaponComponent::StaticClass()));
	_eventBrokerComp = Cast<UEventBrokerComponent>(owner->GetComponentByClass(UEventBrokerComponent::StaticClass()));
	_cameraInterface = Cast<ICharacterCameraInterface>(owner);

	//Initizalize Axis Inputs
	for (auto axisInputClass : _presetAxisClass)
	{
		if (axisInputClass == nullptr)
		{
			continue;
		}
		if (_mapAxisIns.Contains(axisInputClass.GetDefaultObject()->GetBindingName()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Exist duplicate button input class"))
				continue;
		}

		UAxisInputBase* axisInputIns = NewObject<UAxisInputBase>(this, axisInputClass);
		check(axisInputIns)
		axisInputIns->Init(this);
		_mapAxisIns.Add(axisInputIns->GetBindingName(), axisInputIns);
	}

	//Initizalize Button Inputs
	for (auto buttonInputClass : _presetButtonClass)
	{
		if (buttonInputClass == nullptr)
		{
			continue;
		}
		if (_mapButtonIns.Contains(buttonInputClass.GetDefaultObject()->GetBindingName()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Exist duplicate button input class"))
			continue;
		}
	
		UButtonInputBase* buttonInputIns = NewObject<UButtonInputBase>(this, buttonInputClass);
		check(buttonInputIns)
		buttonInputIns->Init(this);
		_mapButtonIns.Add(buttonInputIns->GetBindingName(), buttonInputIns);
	}
}

void UInputPresetBase::VTick(float deltaTime)
{
	//Handle Button pressing
	for (auto buttonInput : _mapButtonIns)
	{
		if (buttonInput.Value)
		{
			buttonInput.Value->Pressing(deltaTime);
		}
	}
}

void UInputPresetBase::HandleAxis(FName inputBindingName, float value)
{
	if (_mapAxisIns.Contains(inputBindingName))
	{
		_mapAxisIns[inputBindingName]->VHandleInputAxis(value);
	}
}

void UInputPresetBase::HandleButtonPressed(FName inputBindingName)
{
	if (_mapButtonIns.Contains(inputBindingName))
	{
		_mapButtonIns[inputBindingName]->Press();
	}
}

void UInputPresetBase::HandleButtonReleased(FName inputBindingName)
{
	if (_mapButtonIns.Contains(inputBindingName))
	{
		_mapButtonIns[inputBindingName]->Release();
	}
}

void UInputPresetBase::RegisterAxisInput(UAxisInputBase* axisInput)
{
	if (!axisInput) return;

	if (_mapAxisIns.Contains(axisInput->GetBindingName()) == false)
	{
		_mapAxisIns.Add(axisInput->GetBindingName(),axisInput);
	}
}

void UInputPresetBase::RegisterButtonInput(UButtonInputBase* buttonInput)
{
	if (!buttonInput) return;

	if (_mapButtonIns.Contains(buttonInput->GetBindingName()) == false)
	{
		_mapButtonIns.Add(buttonInput->GetBindingName(), buttonInput);
	}
}

FORCEINLINE_DEBUGGABLE UActionComponent* UInputPresetBase::GetActionComp()
{
	return _actionComp;
}

FORCEINLINE_DEBUGGABLE UWeaponComponent* UInputPresetBase::GetWeaponComp()
{
	return _weaponComp;
}

FORCEINLINE_DEBUGGABLE UEventBrokerComponent* UInputPresetBase::GetEventBrokerComp()
{
	return _eventBrokerComp;
}

FORCEINLINE_DEBUGGABLE ICharacterCameraInterface* UInputPresetBase::GetCameraInterface()
{
	return _cameraInterface;
}

