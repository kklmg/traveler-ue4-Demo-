// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BillBoardWidget.h"
//#include "GameFramework/Actor.h"
//#include "Kismet/GameplayStatics.h"

void UBillBoardWidget::Initialize(AActor* widgetOwner)
{
	_widgetOwner = widgetOwner;
}

void UBillBoardWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

AActor* UBillBoardWidget::GetWidgetOwner()
{
	return _widgetOwner;
}
