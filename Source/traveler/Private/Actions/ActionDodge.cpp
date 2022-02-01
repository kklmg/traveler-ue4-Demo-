// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionDodge.h"
#include "Character/CreatureCharacter.h"



UActionDodge::UActionDodge()
{
	_actionName = ActionName::DODGE;
	_actionType = EActionType::EACT_Dodge;
	_bInstantAction = false;
	_dodgeSpeed = 250;
}

void UActionDodge::VTMExecute()
{
	ACharacter* actionOwner = GetActionOwner();
	check(actionOwner != nullptr);

	UAnimInstance* animInstance = actionOwner->GetMesh()->GetAnimInstance();

	if (_aniMontage && animInstance)
	{
		//bind 
		animInstance->OnMontageEnded.AddDynamic(this, &UActionDodge::OnAnimMontageFinished);

		//play montage
		actionOwner->PlayAnimMontage(_aniMontage);
	}
}

void UActionDodge::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	GetActionOwner()->AddMovementInput(GetActionOwner()->GetActorForwardVector(), _dodgeSpeed * deltaTime);
}


void UActionDodge::OnAnimMontageFinished(UAnimMontage* montage,bool interrupted)
{
	if(montage != _aniMontage)return;
	if(GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;

	UAnimInstance* animInstance = GetActionOwner()->GetMesh()->GetAnimInstance();
	if (animInstance == nullptr) return;

	animInstance->OnMontageEnded.RemoveDynamic(this, &UActionDodge::OnAnimMontageFinished);
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("End Dodge animation"));

	SetActionProcessSucceed();
}