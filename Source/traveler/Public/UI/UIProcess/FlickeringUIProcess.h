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
	virtual void VTMInit() override;
	
	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;
	virtual void VTMOnDead() override;
	virtual void VTMOnSucceed() override;
	virtual void VTMOnFailed() override;
	virtual void VTMOnAborted() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _opacityCurve;

	float _duration;
	float _elapsedTime;
};
