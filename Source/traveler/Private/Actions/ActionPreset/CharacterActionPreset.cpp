// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionPreset/CharacterActionPreset.h"


void UCharacterActionPreset::VInitialize(ACharacter* character, UActionComponent* actionComp)
{
	Super::VInitialize(character, actionComp);

	MakeActionIns(ActionMoveClass, character, actionComp);
	MakeActionIns(ActionSprintClass, character, actionComp);
	MakeActionIns(ActionJumpClass, character, actionComp);
	MakeActionIns(ActionAimClass, character, actionComp);
	MakeActionIns(ActionDodgeClass, character, actionComp);
}

void UCharacterActionPreset::VEnter()
{
	Super::VEnter();
}
void UCharacterActionPreset::VLeave()
{
	Super::VLeave();
}