// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/CharacterActionPreset.h"


void UCharacterActionPreset::VInitialize()
{
	Super::VInitialize();

	AddActionClassToMap(ActionMoveClass);
	AddActionClassToMap(ActionSprintClass);
	AddActionClassToMap(ActionJumpClass);
	AddActionClassToMap(ActionAimClass);
	AddActionClassToMap(ActionDodgeClass);
}

void UCharacterActionPreset::VEnter()
{
	Super::VEnter();
}
void UCharacterActionPreset::VLeave()
{
	Super::VLeave();
}