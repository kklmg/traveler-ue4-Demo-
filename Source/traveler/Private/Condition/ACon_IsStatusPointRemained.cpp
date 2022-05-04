// Fill out your copyright notice in the Description page of Project Settings.


#include "Condition/ACon_IsStatusPointRemained.h"
#include "Components/StatusComponent.h"
#include "Data/MyDelegates.h"
#include "Status/BasicStatus.h"

void UACon_IsStatusPointRemained::VSetActor(AActor* actor)
{
	Super::VSetActor(actor);

	_statusComp = Cast<UStatusComponent>(actor->GetComponentByClass(UStatusComponent::StaticClass()));
	check(_statusComp);

	UBasicStatus* statusIns = _statusComp->GetBasicStatusIns(_statusType);
	if (statusIns)
	{
		statusIns->OnRemainingValueChanged.AddDynamic(this, &UACon_IsStatusPointRemained::OnRemainingValueChanged);
	}

}

bool UACon_IsStatusPointRemained::VTMValidate()
{
	if (!Super::VTMValidate()) return false;
	float value = _statusComp->GetRemainingValue(_statusType);

	return value > 0.0f;
}

void UACon_IsStatusPointRemained::OnRemainingValueChanged(float prevValue, float newValue)
{
	Validate();
}