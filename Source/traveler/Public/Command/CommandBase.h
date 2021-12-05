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
	virtual void VExecute() PURE_VIRTUAL(UcommandBase::VExecute);

	virtual void VUndo() PURE_VIRTUAL(UcommandBase::VUndo);
};
