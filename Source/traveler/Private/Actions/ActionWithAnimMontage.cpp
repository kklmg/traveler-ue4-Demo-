// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWithAnimMontage.h"
#include "Character/CreatureCharacter.h"
#include "Components/AnimControlComponent.h"

UActionWithAnimMontage::UActionWithAnimMontage()
{
	_bIsInstantProcess = false;
}

bool UActionWithAnimMontage::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	if (GetAnimControlComp() == nullptr)
	{
		UE_LOG(LogAction, Warning, TEXT("ActionWithAnimMontage: No AnimControlComponent"));
		return false;
	}
	else if (GetAnimControlComp()->GetAnimInstance() == nullptr)
	{
		UE_LOG(LogAction, Warning, TEXT("ActionWithAnimMontage: No AnimInstance"));
		return false;
	}
	else if(GetAnimControlComp()->ContainsAnimMontage(_animMontageType) == false)
	{
		UE_LOG(LogAction, Warning, TEXT("ActionWithAnimMontage: No Registered AnimMontageType"));
		return false;
	}
	return true;
}

void UActionWithAnimMontage::VOnExecute()
{
	Super::VOnExecute();

	UAnimInstance* animInstance = GetAnimControlComp()->GetAnimInstance();
	animInstance->OnMontageEnded.AddDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);

	GetAnimControlComp()->PlayAnimMontage(_animMontageType);
}

void UActionWithAnimMontage::VOnDead()
{
	Super::VOnDead();

	GetAnimControlComp()->GetAnimInstance()->OnMontageEnded
		.RemoveDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);

	
	GetAnimControlComp()->StopAnimMontage(_animMontageType);
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
