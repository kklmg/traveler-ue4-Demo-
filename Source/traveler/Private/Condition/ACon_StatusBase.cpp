// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ACon_StatusBase.h"
#include "Components/StatusComponent.h"

void UACon_StatusBase::VSetActor(AActor* actor)
{
	_statusComp = Cast<UStatusComponent>(actor->GetComponentByClass(UStatusComponent::StaticClass()));
}

bool UACon_StatusBase::VTMValidate()
{
	if (!Super::VTMValidate()) return false;

	return _statusComp != nullptr;
}
