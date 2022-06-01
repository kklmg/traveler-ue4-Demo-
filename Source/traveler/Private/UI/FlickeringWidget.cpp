// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FlickeringWidget.h"
#include "Process/CompositeProcessBase.h"
#include "Process/ProcessSectionBase.h"
#include "UI/UIProcess/FlickeringUIProcess.h"
#include "Components/Image.h"


UFlickeringWidget::UFlickeringWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_remainingTime = 10.0f;
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


void UFlickeringWidget::Tick(float deltaTime)
{
	if (_remainingTime <= 0.0f) return;

	_remainingTime -= deltaTime;

	//change flickering rate by remaining time
	UpdateFlickering();

	//Run processes
	_compositeProcess->Tick(deltaTime);

	//update progress bar
	imgProgressBar->GetDynamicMaterial()->SetScalarParameterValue(FName(TEXT("Alpha")), _remainingTime / _widgetData.MaxDuration);
}

void UFlickeringWidget::UpdateFlickering()
{
	while (_curTimeNodeID < _widgetData.FlickeringTimeLineData.Num()
		&& _remainingTime < _widgetData.FlickeringTimeLineData[_curTimeNodeID].RemainingTime)
	{
		_flickeringProcess->SetDuration(_widgetData.FlickeringTimeLineData[_curTimeNodeID].FlickeringDuration);
		_coolingProcess->SetDuration(_widgetData.FlickeringTimeLineData[_curTimeNodeID].CoolingDuration);
		++_curTimeNodeID;
	}
}

void UFlickeringWidget::SetData(FFlickeringWidgetData& widgetData)
{
	_widgetData = widgetData;
	_flickeringProcess->SetOpacityCurve(_widgetData.OpacityCurve);
}

void UFlickeringWidget::SetDuration(float duration)
{
	_remainingTime = duration;

	_curTimeNodeID = 0;
	UpdateFlickering();
}


void UFlickeringWidget::ExecuteFlickeringProcess()
{
	_compositeProcess->Init();
	_compositeProcess->Execute();
}

void UFlickeringWidget::Reset()
{
	_curTimeNodeID = 0;
	_remainingTime = 0.0f;

	_compositeProcess->Init();
}

FFlickeringWidgetData::FFlickeringWidgetData()
{
	MaxDuration = 10.0f;
}
