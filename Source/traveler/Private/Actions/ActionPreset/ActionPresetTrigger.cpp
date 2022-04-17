// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPresetTrigger.h"
#include "Condition/CompositeActorCondition.h"
#include "Actions/ActionPreset/CharacterActionPreset.h"
#include "Components/ActionComponent.h"
#include "Interface/EventBrokerInterface.h"
#include "GameSystem/DebugMessageHelper.h"


void UActionPresetTrigger::Initiazlie(UActionComponent* actionComponent)
{
	if (!actionComponent) return;
	_actionComponent = actionComponent;

	if (_conditionClass)
	{
		_conditionIns = NewObject<UCompositeActorCondition>(this, _conditionClass);
		_conditionIns->SetActor(_actionComponent->GetOwner());
		_conditionIns->Initialize();
		_conditionIns->OnValidated.AddUObject(this, &UActionPresetTrigger::OnValidate);
		_conditionIns->Validate();
	}

	if (_actionPresetClass)
	{
		_actionPresetIns = NewObject<UCharacterActionPreset>(this, _actionPresetClass);
		_actionPresetIns->VInitialize();
	}
	
}

void UActionPresetTrigger::OnValidate(bool result)
{
	if (_actionComponent && _actionPresetIns && _conditionIns && result)
	{
		_actionComponent->SwitchActionSet(_actionPresetIns);
	}
}
