// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FlickeringWidget.h"
#include "Process/CompositeProcessBase.h"
#include "Process/ProcessSectionBase.h"
#include "UI/UIProcess/FlickeringUIProcess.h"


UFlickeringWidget::UFlickeringWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_duration = 15;
}

bool UFlickeringWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!_compositeProcess)
	{
		_compositeProcess = NewObject<UCompositeProcessBase>(this);

		//setup flickering process
		_flickeringProcess = NewObject<UFlickeringUIProcess>(this);
		

		//setup cooling process
		_coolingProcess = NewObject<UProcessSectionBase>(this);

		_compositeProcess->AddProcess(_flickeringProcess);
		_compositeProcess->AddProcess(_coolingProcess);
	}

	_compositeProcess->setIsLoop(true);
	_flickeringProcess->SetWidget(this);

	return true;
}

void UFlickeringWidget::NativeConstruct()
{
	Super::NativeConstruct();
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

void UFlickeringWidget::SetDuration(float duration)
{
	_duration = duration;
}

void UFlickeringWidget::SetOpacityCurve(UCurveFloat* curve)
{
	_opacityCurve = curve;
}

void UFlickeringWidget::SetTimeLineData(TArray<FTimeFrameFlickeringData> timeLineData)
{
	_flickeringTimeLineData = timeLineData;
}

void UFlickeringWidget::ExecuteFlickeringProcess()
{
	if (!_flickeringProcess) return;
	if (!_coolingProcess) return;
	if (!_compositeProcess) return;

	if (_currentTimeIndex < _flickeringTimeLineData.Num())
	{
		_flickeringProcess->SetDuration(_flickeringTimeLineData[_currentTimeIndex].FlickeringDuration);
		_flickeringProcess->SetOpacityCurve(_opacityCurve);

		_coolingProcess->SetDuration(_flickeringTimeLineData[_currentTimeIndex].CoolingDuration);

		_compositeProcess->VInitialize();
		_compositeProcess->VExecute();
	}
}

void UFlickeringWidget::Reset()
{
	_currentTimeIndex = 0;
	_elapsedTime = 0.0f;

	//_compositeProcess->VAbort();
	//_compositeProcess->VInitialize();
}
