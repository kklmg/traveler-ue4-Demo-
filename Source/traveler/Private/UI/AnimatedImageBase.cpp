// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AnimatedImageBase.h"
#include "Curves/CurveVector.h"


UAnimatedImageBase::UAnimatedImageBase()
{

}

void UAnimatedImageBase::Initialize()
{
	_startLocation = RenderTransform.Translation;
	_startAngle = RenderTransform.Angle;
}

void UAnimatedImageBase::Animate(float alpha)
{
	FWidgetTransform widgetTransform;

	FVector curveValue = FVector::ZeroVector;
	if(_animCurve)
	{
		curveValue = _animCurve->GetVectorValue(alpha);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AnimCurve applied"));
	}

	widgetTransform.Translation.X = FMath::Lerp(_startLocation.X, _endLocation.X, curveValue.X);
	widgetTransform.Translation.Y = FMath::Lerp(_startLocation.Y, _endLocation.Y, curveValue.Y);
	widgetTransform.Angle = FMath::Lerp(_startAngle, _endAngle, curveValue.Z);

	//widgetTransform.Angle;

	SetRenderTransform(widgetTransform);
}
