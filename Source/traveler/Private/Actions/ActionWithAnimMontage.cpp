// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWithAnimMontage.h"
#include "Character/CreatureCharacter.h"

UActionWithAnimMontage::UActionWithAnimMontage()
{
	_bInstantAction = false;
}

void UActionWithAnimMontage::VTMExecute()
{
	if (GetActionOwner() == nullptr || _aniMontage == nullptr) return;

	UAnimInstance* animInstance = GetActionOwner()->GetMesh()->GetAnimInstance();
	if(animInstance == nullptr) return;

	//subscribe montageEnded event
	animInstance->OnMontageEnded.AddDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);

	//play montage
	GetActionOwner()->PlayAnimMontage(_aniMontage);
}

void UActionWithAnimMontage::VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted)
{
	UAnimInstance* animInstance = GetActionOwner()->GetMesh()->GetAnimInstance();
	if (animInstance == nullptr) return;

	animInstance->OnMontageEnded.RemoveDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);

	if(interrupted)
	{
		SetActionProcessFailed();
	}
	else
	{
		SetActionProcessSucceed();
	}
}
