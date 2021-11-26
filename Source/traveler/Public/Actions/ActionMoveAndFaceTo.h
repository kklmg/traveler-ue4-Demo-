// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ActionMoveAndFaceTo.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionMoveAndFaceTo : public UAction
{
	GENERATED_BODY()
public:
	UActionMoveAndFaceTo();
public:
	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;

private:
	UPROPERTY(EditAnyWhere, Category = animation)
	UAnimMontage* _AniMontage;

};
