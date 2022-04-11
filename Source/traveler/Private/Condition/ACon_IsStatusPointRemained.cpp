// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ACon_IsStatusPointRemained.h"

void UACon_IsStatusPointRemained::VSetActor(AActor* actor)
{
	Super::VSetActor(actor);

	auto statusIns = _statusInterface->VGetBasicStatusIns(_statusType);
	if (statusIns)
	{
		statusIns->OnRemainingValueChanged.AddDynamic(this, &UACon_IsStatusPointRemained::OnRemainingValueChanged);
	}
}

bool UACon_IsStatusPointRemained::VTMValidate()
{
	if (!Super::VTMValidate()) return false;
	float value = _statusInterface->VGetRemainingValue(_statusType);

	return value > 0.0f;
}

void UACon_IsStatusPointRemained::OnRemainingValueChanged(float prevValue, float newValue)
{
	Validate();
}