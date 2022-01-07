// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionBase.h"
#include "ActionIdle.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionIdle : public UActionBase
{
	GENERATED_BODY()
public:
	UActionIdle();

public:
	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;

private:
	UPROPERTY(EditAnyWhere, Category = animation)
	UAnimMontage* _AniMontage;

	UPROPERTY(EditAnyWhere, Category = animation)
	UAnimSequence* _AniSequence;
};
