// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FlickeringWidget.h"
#include "Process/CompositeProcessBase.h"
#include "Process/ProcessSectionBase.h"
#include "UI/UIProcess/FlickeringUIProcess.h"


UFlickeringWidget::UFlickeringWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	_flickeringTime = 2;
	_coolingTime = 2;
}

void UFlickeringWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

		_compositeProcess->VInitialize();
		_compositeProcess->VExecute();
	}
}


void UFlickeringWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_elapsedTime += InDeltaTime;


	if (!_compositeProcess) return;

	_compositeProcess->VTick(InDeltaTime);
}
