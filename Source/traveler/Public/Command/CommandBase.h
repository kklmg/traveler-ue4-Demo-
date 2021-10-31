// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommandBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCommandBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Execute() PURE_VIRTUAL(UcommandBase::Execute);

	virtual void Undo() PURE_VIRTUAL(UcommandBase::Undo);
};
