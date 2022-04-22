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
	float GetElapsedTime();

	virtual void VTMInitialize();
	virtual bool VTMCanExecute();
	virtual void VTMExecute();
	virtual void VTMTick(float deltaTime);

	virtual void VTMOnDead();
	virtual void VTMOnSucceed();
	virtual void VTMOnFailed();
	virtual void VTMOnAborted();	

private:
	float _elapsedTime;
	float _duration;
};
