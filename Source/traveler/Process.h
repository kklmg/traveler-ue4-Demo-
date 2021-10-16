// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Process.generated.h"


enum EProcessState
{
	UNINITIALIZED = 0,  // created but not running

	// Living processes
	RUNNING,  // initialized and running
	PAUSED,  // initialized but paused

	// Dead processes
	SUCCEEDED,  // completed successfully
	FAILED,  // failed to complete
	ABORTED,  // aborted; may not have started
};

/**
 * 
 */
UCLASS()
class TRAVELER_API UProcess : public UObject
{
	GENERATED_BODY()
	
private:
	UProcess* _pChild;
	EProcessState _state;


public:
	// construction
	UProcess();

	virtual void VInit(void);
	virtual void VUpdate(unsigned long deltaMs);
	virtual void VSuccess(void);
	virtual void VFail(void);
	virtual void VAbort(void);

public:
	EProcessState GetState(void) const;
	bool IsAlive(void) const;
	bool IsDead(void) const;
	bool IsPaused(void) const;

	// child functions
	inline void AttachChild(UProcess* pChild);
	UProcess* RemoveChild(void);  // releases ownership of the child
	UProcess* PeekChild(void);  // doesn't release ownership of the child

	void SetState(EProcessState newState);
};
