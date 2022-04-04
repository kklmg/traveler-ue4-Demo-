// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/ActorEventDataBase.h"

void UActorEventDataBase::SetActor(AActor* actor)
{
	_actor = actor;
}

AActor* UActorEventDataBase::GetActor()
{
	return _actor;
}