// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIProcess/UIProcessBase.h"
#include "FlickeringUIProcess.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UFlickeringUIProcess : public UUIProcessBase
{
	GENERATED_BODY()
public:
	void SetDuration(float duration);
	void SetOpacityCurve(UCurveFloat* opacityCurve);

	virtual bool VCanExecute() override;
protected:
	virtual void VOnInit() override;
	
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;
	virtual void VOnDead() override;
	virtual void VOnSucceed() override;
	virtual void VOnFailed() override;
	virtual void VOnAborted() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _opacityCurve;

	float _duration;
	float _elapsedTime;
};
