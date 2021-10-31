// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command/CommandCamera.h"
#include "CommandCameraDrag.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UCommandCameraDrag : public UCommandCamera
{
	GENERATED_BODY()

public:
	void SetOffset();

	virtual void Execute() override;
	virtual void Undo() override;

private:
	FVector _offset;
};
	
