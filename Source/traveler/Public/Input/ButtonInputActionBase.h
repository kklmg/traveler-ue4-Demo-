// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/ButtonInputBase.h"
#include "Enums/EnumActionType.h"
#include "ButtonInputActionBase.generated.h"

class UActionComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UButtonInputActionBase : public UButtonInputBase
{
	GENERATED_BODY()
public:
	void Initialize(UActionComponent* actionComp);

	EActionType GetActionType();
	UActionComponent* GetActionComp();
protected:
	UPROPERTY(EditDefaultsOnly)
	EActionType _actionType;

private:
	UPROPERTY()
	UActionComponent* _actionComp;
};
