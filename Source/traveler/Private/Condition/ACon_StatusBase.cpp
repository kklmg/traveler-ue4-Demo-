// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ACon_StatusBase.h"

void UACon_StatusBase::VSetActor(AActor* actor)
{
	_statusInterface = Cast<IStatusInterface>(actor);
}

bool UACon_StatusBase::VTMValidate()
{
	if (!Super::VTMValidate()) return false;

	return _statusInterface != nullptr;
}
