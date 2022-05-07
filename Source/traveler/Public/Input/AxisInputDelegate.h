// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/AxisInputBase.h"
#include "AxisInputDelegate.generated.h"

DECLARE_DELEGATE_OneParam(FD_AxisInput, float)

/**
 * 
 */
UCLASS()
class TRAVELER_API UAxisInputDelegate : public UAxisInputBase
{
	GENERATED_BODY()
public:
	virtual void VHandleInputAxis(float value) override;

	template<typename TObj>
	void BindAxisInput(TObj* inUserObj, void (TObj::* inFunc)(float));
protected:
	FD_AxisInput _axisInputDelegate;

public:
	template<typename TData>
	static UAxisInputDelegate* MakeInstance(UObject* outer, FName inputBindingName, TData* inUserObj, void(TData::* inFunc)(float));
};

template<typename TObj>
inline void UAxisInputDelegate::BindAxisInput(TObj* inUserObj, void(TObj::* inFunc)(float))
{
	return _axisInputDelegate.BindUObject(inUserObj, inFunc);
}

template<typename TObj>
inline UAxisInputDelegate* UAxisInputDelegate::MakeInstance(UObject* outer, FName inputBindingName, TObj* inUserObj, void(TObj::* inFunc)(float))
{
	UAxisInputDelegate* axisInput = NewObject<UAxisInputDelegate>(outer);
	axisInput->SetBindingName(inputBindingName);
	axisInput->BindAxisInput<TObj>(inUserObj, inFunc);

	return axisInput;
}
