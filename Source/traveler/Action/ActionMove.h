// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ActionMove.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionMove : public UAction
{
	GENERATED_BODY()

public:
	UActionMove();
	UActionMove(APawn* pawn, FVector direction,float scale);
	
	virtual void VUpdate(unsigned long deltaMs) override;

private:
	APawn* _pPawn;
	FVector _direction;
	float _scale;
};
