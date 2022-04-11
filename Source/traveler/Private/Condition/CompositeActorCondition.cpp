// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/CompositeActorCondition.h"
#include "Condition/ActorCondition.h"


void UCompositeActorCondition::SetActor(AActor* actor)
{
	_actor = actor;
}

void UCompositeActorCondition::VInitialize()
{
	Super::VInitialize();

	for (auto conditionClass : _actorConditionClasses)
	{
		if (!conditionClass) continue;

		UActorCondition* conditionIns = NewObject<UActorCondition>(this, conditionClass);
		if (!conditionIns) continue;

		conditionIns->VSetActor(_actor);
		conditionIns->VInitialize();
		conditionIns->OnValidate.AddUObject(this, &UCompositeCondition::OnSubConditionChanged);
		this->Add(conditionIns);
	}
}