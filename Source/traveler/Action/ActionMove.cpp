// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionMove.h"
UActionMove::UActionMove() {}
UActionMove::UActionMove(APawn* pPawn, FVector direction, float scale) : _pPawn(pPawn), _direction(direction), _scale(scale) {}

void UActionMove::VUpdate(unsigned long deltaMs)
{
	if (_pPawn)
	{
		_pPawn->AddMovementInput(_direction, _scale * deltaMs);
		UProcess::SetState(EProcessState::SUCCEEDED);
	}
}