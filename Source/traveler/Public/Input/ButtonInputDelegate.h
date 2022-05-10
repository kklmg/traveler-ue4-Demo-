// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "ButtonInputDelegate.generated.h"

DECLARE_DELEGATE(FD_OnButtonPressed)
DECLARE_DELEGATE(FD_OnButtonReleased)
DECLARE_DELEGATE_OneParam(FD_OnButtonPressing,float)

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputDelegate : public UButtonInputBase
{
	GENERATED_BODY()
public:

	UButtonInputDelegate();

	template<typename TObj>
	void BindButtonPressed(TObj* inUserObj, void (TObj::* inFunc)());

	template<typename TObj>
	void BindButtonReleased(TObj* inUserObj, void (TObj::* inFunc)());

	template<typename TObj>
	void BindButtonPressing(TObj* inUserObj, void (TObj::* inFunc)(float));

protected:
	virtual void VOnPressed() override;
	virtual void VOnPressing(float deltaTime) override;
	virtual void VOnReleased() override;

private:
	FD_OnButtonPressed _onButtonPressed;
	FD_OnButtonPressing _onButtonPressing;
	FD_OnButtonReleased _onButtonReleased;

public:
	template<typename TObj>
	static UButtonInputDelegate* MakeInstance(UObject* outer, FName inputBindingName, TObj* inUserObj,
		void(TObj::* buttonPressed)(), void(TObj::* buttonReleased)() = nullptr, void(TObj::* buttonPressing)(float) = nullptr);
};

template<typename TObj>
inline void UButtonInputDelegate::BindButtonPressed(TObj* inUserObj, void(TObj::* inFunc)())
{
	_onButtonPressed.BindUObject(inUserObj, inFunc);
}

template<typename TObj>
inline void UButtonInputDelegate::BindButtonReleased(TObj* inUserObj, void(TObj::* inFunc)())
{
	_onButtonReleased.BindUObject(inUserObj, inFunc);
}

template<typename TObj>
inline void UButtonInputDelegate::BindButtonPressing(TObj* inUserObj, void(TObj::* inFunc)(float))
{
	_onButtonPressing.BindUObject(inUserObj, inFunc);
}

template<typename TObj>
static UButtonInputDelegate* UButtonInputDelegate::MakeInstance(UObject* outer, FName inputBindingName, TObj* inUserObj,
	void(TObj::* buttonPressed)(), void(TObj::* buttonReleased)(), void(TObj::* buttonPressing)(float))
{
	if (inUserObj == nullptr)
	{
		return nullptr;
	}

	UButtonInputDelegate* buttonInput = NewObject<UButtonInputDelegate>(outer);
	buttonInput->SetBindingName(inputBindingName);

	if (buttonPressed) 
	{
		buttonInput->BindButtonPressed<TObj>(inUserObj, buttonPressed);
	}

	if (buttonReleased)
	{
		buttonInput->BindButtonReleased<TObj>(inUserObj, buttonReleased);
	}

	if (buttonPressing)
	{
		buttonInput->BindButtonPressing<TObj>(inUserObj, buttonPressing);
	}
		
	return buttonInput;
}



//template<typename TObj>
//void BindAxisInput(TObj* inUserObj, void (TObj::* inFunc)(float));
//protected:
//	FD_AxisInput _axisInputDelegate;
//

//};
//
//template<typename TObj>
//inline void UAxisInputDelegate::BindAxisInput(TObj* inUserObj, void(TObj::* inFunc)(float))
//{
//	return _axisInputDelegate.BindUObject(inUserObj, inFunc);
//}
//
//template<typename TObj>
//inline UAxisInputDelegate* UAxisInputDelegate::MakeInstance(UObject* outer, FName inputBindingName, TObj* inUserObj, void(TObj::* inFunc)(float))
//{
//	UAxisInputDelegate* axisInput = NewObject<UAxisInputDelegate>(outer);
//	axisInput->SetBindingName(inputBindingName);
//	axisInput->BindAxisInput<TObj>(inUserObj, inFunc);
//
//	return axisInput;
//}
