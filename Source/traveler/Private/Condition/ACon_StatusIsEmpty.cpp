// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ACon_StatusIsEmpty.h"

void UACon_StatusIsEmpty::VSetActor(AActor* actor)
{
	Super::VSetActor(actor);

	auto statusIns = _statusInterface->VGetBasicStatusIns(_statusType);
	if (statusIns)
	{
		statusIns->OnRemainingValueChanged.AddDynamic(this, &UACon_StatusIsEmpty::OnRemainingValueChanged);
	}
}

bool UACon_StatusIsEmpty::VTMValidate()
{
	if (!Super::VTMValidate()) return false;
	float value = _statusInterface->VGetRemainingValue(_statusType);

	return value > 0.0f;
}

void UACon_StatusIsEmpty::OnRemainingValueChanged(float prevValue, float newValue)
{
	Validate();
}