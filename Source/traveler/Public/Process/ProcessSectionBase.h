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
	virtual void VTMEnter();
	virtual void VTMTick(float deltaTime);
	virtual void VTMEnd();
	virtual void VTMReset();

	float GetElapsedTime();
	

private:
	float _elapsedTime;
};
