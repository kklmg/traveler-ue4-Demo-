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
	virtual void VBegin(AActor* actor, UActionData* actionData) override;

	virtual void VUpdate(float deltaTime, AActor* actor, UActionData* data) override;

private:
	UPROPERTY(EditAnyWhere, Category = animation)
	UAnimMontage* _AniMontage;

};
