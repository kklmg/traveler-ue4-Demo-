// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ActorCondition.h"

void UActorCondition::SetActor(AActor* actor)
{
	_actor = actor;
}

AActor* UActorCondition::GetActor()
{
	return _actor;
}
