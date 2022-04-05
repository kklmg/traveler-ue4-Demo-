// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/ActionPresetTrigger.h"
#include "Condition/CompositeCondition.h"
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
		_conditionIns = NewObject<UCompositeCondition>(this, _conditionClass);
		_conditionIns->VInitialize();
	}

	IEventBrokerInterface* eventBroker = actionComponent->GetEventBrokerInterface();
	if (_conditionIns && eventBroker)
	{
		//subscribe
		TArray<FName> eventNames = _conditionIns->VGetReactiveEventNames();
		for (FName eventName : eventNames)
		{
			eventBroker->VGetEventDelegate(eventName).AddUObject(this, &UActionPresetTrigger::Validate);
		}
	}

	if (_actionPresetClass)
	{
		_actionPresetIns = NewObject<UCharacterActionPreset>(this, _actionPresetClass);
		_actionPresetIns->VInitialize();
	}
	
}

void UActionPresetTrigger::Validate(UEventDataBase* eventData)
{
	//UDebugMessageHelper::Messsage_String("try  to", outName);

	if (_actionComponent && _actionPresetIns && _conditionIns && _conditionIns->VValidate(eventData))
	{
		_actionComponent->SwitchActionSet(_actionPresetIns);
		FString outName;
		_actionPresetIns->GetName(outName);

		UDebugMessageHelper::Messsage_String("Swtich to",outName);
	}
}
