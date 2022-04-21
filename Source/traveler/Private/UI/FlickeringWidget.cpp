// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FlickeringWidget.h"
#include "Process/CompositeProcessBase.h"
#include "Process/ProcessSectionBase.h"
#include "UI/UIProcess/FlickeringUIProcess.h"


UFlickeringWidget::UFlickeringWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_totalDuration = 15;
}

bool UFlickeringWidget::Initialize()
{
	return Super::Initialize();
}

void UFlickeringWidget::NativeConstruct()
{
	Super::NativeConstruct();

	_compositeProcess = NewObject<UCompositeProcessBase>(this);
	_compositeProcess->setIsLoop(true);

	//setup flickering process
	_flickeringProcess = NewObject<UFlickeringUIProcess>(this);
	_flickeringProcess->SetWidget(this);

	//setup cooling process
	_coolingProcess = NewObject<UProcessSectionBase>(this);

	_compositeProcess->AddProcess(_flickeringProcess);
	_compositeProcess->AddProcess(_coolingProcess);
}


void UFlickeringWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_elapsedTime > _totalDuration) return;

	_elapsedTime += InDeltaTime;
	float remainingTime = _totalDuration - _elapsedTime;

	//change flickering rate by remaining time
	while (_curTimeNodeID < _widgetData.FlickeringTimeLineData.Num()
		&& remainingTime < _widgetData.FlickeringTimeLineData[_curTimeNodeID].TimePoint)
	{
		_flickeringProcess->SetDuration(_widgetData.FlickeringTimeLineData[_curTimeNodeID].FlickeringDuration);
		_coolingProcess->SetDuration(_widgetData.FlickeringTimeLineData[_curTimeNodeID].CoolingDuration);

		++_curTimeNodeID;
	}

	//Run processes
	_compositeProcess->Tick(InDeltaTime);
}

void UFlickeringWidget::SetData(FFlickeringWidgetData& widgetData)
{
	_widgetData = widgetData;
}

void UFlickeringWidget::SetDuration(float duration)
{
	_totalDuration = duration;
}


void UFlickeringWidget::ExecuteFlickeringProcess()
{
	if (_curTimeNodeID < _widgetData.FlickeringTimeLineData.Num())
	{
		_flickeringProcess->SetDuration(_widgetData.FlickeringTimeLineData[_curTimeNodeID].FlickeringDuration);
		_flickeringProcess->SetOpacityCurve(_widgetData.OpacityCurve);

		_coolingProcess->SetDuration(_widgetData.FlickeringTimeLineData[_curTimeNodeID].CoolingDuration);

		_compositeProcess->Init();
		_compositeProcess->Execute();
	}
}

void UFlickeringWidget::Reset()
{
	_curTimeNodeID = 0;
	_elapsedTime = 0.0f;

	_compositeProcess->Init();
}
