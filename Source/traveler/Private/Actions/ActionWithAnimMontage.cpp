// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWithAnimMontage.h"
#include "Character/CreatureCharacter.h"
#include "Components/AnimControlComponent.h"

UActionWithAnimMontage::UActionWithAnimMontage()
{
	_bIsInstantProcess = false;
}

void UActionWithAnimMontage::VTMExecute()
{
	Super::VTMExecute();

	check(GetActionOwner());

	if(GetAnimControlComp() && GetAnimControlComp()->GetAnimInstance())
	{
		UAnimInstance* animInstance = GetAnimControlComp()->GetAnimInstance();
	
		if(animInstance && GetAnimControlComp()->PlayAnimMontage(_animMontageType))
		{
			//subscribe montageEnded event
			animInstance->OnMontageEnded.AddDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);
		}
		else
		{
			SetProcessFailed();
		}
	}
	else
	{
		SetProcessFailed();
	}
}

void UActionWithAnimMontage::VTMOnDead()
{
	check(GetAnimControlComp()->GetAnimInstance());

	GetAnimControlComp()->GetAnimInstance()->OnMontageEnded
		.RemoveDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);
}

void UActionWithAnimMontage::VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted)
{
	if (interrupted)
	{
		SetProcessAborted();
	}
	else
	{
		SetProcessSucceed();
	}
}
