// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionSpreadAttack.h"
#include "GameFramework/Character.h"

UActionSpreadAttack::UActionSpreadAttack()
{
	_actionName = ActionName::SPREADATTACK;
	_bInstantAction = false;
}

void UActionSpreadAttack::VExecute()
{
	Super::VExecute();

	if(_animMontage)
	{
		GetActionOwner().PlayAnimMontage(_animMontage);

		//_animMontage->Notifies.
	}

	



}

void UActionSpreadAttack::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

}
