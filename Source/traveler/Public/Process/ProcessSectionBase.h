// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "ProcessSectionBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UProcessSectionBase : public UProcessBase
{
	GENERATED_BODY()
public:
	void SetDuration(float duration);
	float GetRemainingTime();

	virtual void VTMInitialize();
	virtual bool VCanExecute() override;
	virtual void VOnExecute();
	virtual void VOnTick(float deltaTime);

	virtual void VOnDead();
	virtual void VOnSucceed();
	virtual void VOnFailed();
	virtual void VOnAborted();	

private:
	float _remainingTime;
	float _duration;
};
