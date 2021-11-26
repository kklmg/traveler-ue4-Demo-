// Fill out your copyright notice in the Description page of Project Settings.


#include "State/CharacterStateBase.h"
#include "Components/ActionComponent.h"




void UCharacterStateBase::VEnter() 
{
	Super::VEnter();

	AddActionClass(ActionMoveClass);
	AddActionClass(ActionSprintClass);
	AddActionClass(ActionJumpClass);
	AddActionClass(ActionAimClass);
	AddActionClass(ActionDodgeClass);
}
void UCharacterStateBase::VLeave()
{
	Super::VLeave();
}