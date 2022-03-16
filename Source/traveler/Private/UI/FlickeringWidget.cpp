// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FlickeringWidget.h"
#include "Process/CompositeProcessBase.h"
#include "Process/ProcessSectionBase.h"
#include "UI/UIProcess/FlickeringUIProcess.h"


UFlickeringWidget::UFlickeringWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_flickeringDuration = 2;
	_coolingDuration = 2;
	_duration = 15;
}

void UFlickeringWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!_compositeProcess)
	{
		_compositeProcess = NewObject<UCompositeProcessBase>(this);
		_compositeProcess->setIsLoop(true);

		//setup flickering process
		_flickeringProcess = NewObject<UFlickeringUIProcess>(this);
		_flickeringProcess->SetWidget(this);
		_flickeringProcess->SetDuration(_flickeringDuration);
		_flickeringProcess->SetOpacityCurve(_opactiryCurve);
		
		//setup cooling process
		_coolingProcess = NewObject<UProcessSectionBase>(this);
		_coolingProcess->SetDuration(_coolingDuration);

		_compositeProcess->AddProcess(_flickeringProcess);
		_compositeProcess->AddProcess(_coolingProcess);

		_compositeProcess->VInitialize();
		_compositeProcess->VExecute();
	}
}


void UFlickeringWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_elapsedTime += InDeltaTime;
	float remainingTime = _duration - _elapsedTime;

	//change flickering rate by remaining time
	while (_currentTimeIndex < _flickeringTimeLineData.Num() 
		&& remainingTime < _flickeringTimeLineData[_currentTimeIndex].onRemainingTime)
		{
			_flickeringProcess->SetDuration(_flickeringTimeLineData[_currentTimeIndex].FlickeringDuration);
			_coolingProcess->SetDuration(_flickeringTimeLineData[_currentTimeIndex].CoolingDuration);

			++_currentTimeIndex;
		}

	if (!_compositeProcess) return;

	_compositeProcess->VTick(InDeltaTime);
}
