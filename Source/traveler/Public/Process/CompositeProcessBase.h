// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "CompositeProcessBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCompositeProcessBase : public UProcessBase
{
	GENERATED_BODY()

public:
	void AddProcess(UProcessBase* process);
	void setIsLoop(bool isLoop);

	virtual void VTMInitialize() override;
	virtual bool VTMCanExecute() override;
	virtual void VTMExecute() override;
	virtual FName VGetProcessName() override;
	virtual bool VIsInstantProcess() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;
	virtual void VTMReset() override;
	virtual void VTMOnAborted() override;

private:
	UPROPERTY()
	TArray<UProcessBase*> _procesPool;

	UPROPERTY(EditDefaultsOnly)
	FName _processName;

	bool _bLoop;
	int32 _curProcessID;
};
