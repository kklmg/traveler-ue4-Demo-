// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ACon_StatusBase.h"
#include "Status/EnumStatus.h"
#include "ACon_IsStatusPointRemained.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UACon_IsStatusPointRemained : public UACon_StatusBase
{
	GENERATED_BODY()
public:
	virtual void VSetActor(AActor* actor) override;
protected:
	virtual bool VOnValidated() override;

	UFUNCTION()
	void OnRemainingValueChanged(float prevValue,float newValue);

private:
	UPROPERTY(EditDefaultsOnly)
	EStatusType _statusType;

	UPROPERTY()
	UStatusComponent* _statusComp;
};
