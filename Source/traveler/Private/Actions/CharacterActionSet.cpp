// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CharacterActionSet.h"


void UCharacterActionSet::VEnter()
{
	Super::VEnter();

	AddActionClass(ActionMoveClass);
	AddActionClass(ActionSprintClass);
	AddActionClass(ActionJumpClass);
	AddActionClass(ActionAimClass);
	AddActionClass(ActionDodgeClass);
}
void UCharacterActionSet::VLeave()
{
	Super::VLeave();
}