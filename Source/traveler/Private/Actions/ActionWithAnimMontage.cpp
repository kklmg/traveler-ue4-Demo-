// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionWithAnimMontage.h"
#include "Character/CreatureCharacter.h"

UActionWithAnimMontage::UActionWithAnimMontage()
{
	_bInstantAction = false;
}

void UActionWithAnimMontage::VExecute()
{
	Super::VExecute();

	if (_actionOwner == nullptr || _aniMontage == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(_actionOwner);
	if (character == nullptr) return;

	UAnimInstance* animInstance = _actionOwner->GetMesh()->GetAnimInstance();
	if(animInstance == nullptr) return;

	//subscribe montageEnded event
	animInstance->OnMontageEnded.AddDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);

	//play montage
	character->PlayAnimMontage(_aniMontage);
}

void UActionWithAnimMontage::VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted)
{
	if (montage != _aniMontage)return;
	if (_actionOwner == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(_actionOwner);
	if (character == nullptr) return;

	UAnimInstance* animInstance = _actionOwner->GetMesh()->GetAnimInstance();
	if (animInstance == nullptr) return;

	animInstance->OnMontageEnded.RemoveDynamic(this, &UActionWithAnimMontage::VOnAnimMontageFinished);

	_state = interrupted ? EActionProcessState::EAPS_FAILED : EActionProcessState::EAPS_SUCCEEDED;
}
