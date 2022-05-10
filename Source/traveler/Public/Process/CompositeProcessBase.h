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
	UCompositeProcessBase();

	void AddProcess(UProcessBase* process);
	void setIsLoop(bool isLoop);

	virtual void VOnInit() override;
	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;
	virtual void VOnDead() override;
	virtual void VOnAborted() override;

private:
	UPROPERTY()
	TArray<UProcessBase*> _procesPool;

	bool _bLoop;
	int32 _curProcessID;
};
