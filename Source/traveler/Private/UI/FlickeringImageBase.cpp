// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FlickeringImageBase.h"
#include "Process/CompositeProcessBase.h"
#include "Process/ProcessSectionBase.h"
#include "UI/UIProcess/FlickeringUIProcess.h"

void UFlickeringImageBase::Initialize()
{
	if (!_compositeProcess) 
	{
		_compositeProcess = NewObject<UCompositeProcessBase>(this);

		//setup flickering process
		UFlickeringUIProcess* flickeringProcess = NewObject<UFlickeringUIProcess>(this);
		flickeringProcess->SetData(_flickeringTime, _opactiryCurve);

		//setup cooling process
		UProcessSectionBase* coolingProcess = NewObject<UProcessSectionBase>(this);
		coolingProcess->SetDuration(_coolingTime);
	
		_compositeProcess->AddProcess(flickeringProcess);
		_compositeProcess->AddProcess(coolingProcess);
	}
}

void UFlickeringImageBase::Tick(float deltaTime)
{
	if (_compositeProcess)
	{
		_compositeProcess->VTick(deltaTime);
	}	
}
