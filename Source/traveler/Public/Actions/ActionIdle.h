// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ActionIdle.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionIdle : public UAction
{
	GENERATED_BODY()
public:
	UActionIdle();

public:
	virtual void VBegin(AActor* actor, UActionData* actionData) override;

	virtual void VUpdate(float deltaTime, AActor* actor, UActionData* data) override;

private:
	UPROPERTY(EditAnyWhere, Category = animation)
	UAnimMontage* _AniMontage;

	UPROPERTY(EditAnyWhere, Category = animation)
	UAnimSequence* _AniSequence;
};
