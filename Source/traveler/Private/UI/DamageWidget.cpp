// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageWidget.h"

FDamageWidgetData::FDamageWidgetData()
{
	TextScale = FVector2D::UnitVector;
	ScrollSpeed = 10.0f;
	ScrollDirection = FVector2D(0.0f, 1.0f);
	Life = 5.0f;
}

void UDamageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) 
{
	ElapsedTime += InDeltaTime;

	FVector2D scrollOffset = DamageWidgetData.ScrollDirection * DamageWidgetData.ScrollSpeed * InDeltaTime;
	
	SetRenderTranslation(RenderTransform.Translation + scrollOffset);
}


void UDamageWidget::SetData(float damageAmount, FDamageWidgetData damageWidgetData)
{
	Damage = damageAmount;
	DamageWidgetData = damageWidgetData;
}

bool UDamageWidget::IsLifeOver()
{
	return ElapsedTime > DamageWidgetData.Life;
}
