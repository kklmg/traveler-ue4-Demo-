// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/CharacterActionPreset.h"


void UCharacterActionPreset::VEnter()
{
	Super::VEnter();

	AddActionClass(ActionMoveClass);
	AddActionClass(ActionSprintClass);
	AddActionClass(ActionJumpClass);
	AddActionClass(ActionAimClass);
	AddActionClass(ActionDodgeClass);
}
void UCharacterActionPreset::VLeave()
{
	Super::VLeave();
}