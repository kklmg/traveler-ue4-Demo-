// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionDodge.h"
#include "Character/CreatureCharacter.h"



UActionDodge::UActionDodge()
{
	_actionName = ActionName::DODGE;
	_bInstantAction = false;
	_dodgeSpeed = 250;
}

void UActionDodge::VExecute()
{
	Super::VExecute();

	check(_actionOwner != nullptr);
	ACreatureCharacter* character = Cast<ACreatureCharacter>(_actionOwner);
	check(character != nullptr);

	UAnimInstance* animInstance = _actionOwner->GetMesh()->GetAnimInstance();

	if (_aniMontage && animInstance)
	{
		//bind 
		animInstance->OnMontageEnded.AddDynamic(this, &UActionDodge::OnAnimationFinished);

		//play montage
		character->PlayAnimMontage(_aniMontage);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("play Dodge animation"));
		character->SetCharacterState(ECharacterState::CS_GroundDodging);
	}
}

void UActionDodge::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

	_actionOwner->AddMovementInput(_actionOwner->GetActorForwardVector(), _dodgeSpeed * deltaTime);
}


void UActionDodge::OnAnimationFinished(UAnimMontage* montage,bool interrupted)
{
	check(_actionOwner != nullptr);
	ACreatureCharacter* character = Cast<ACreatureCharacter>(_actionOwner);
	check(character != nullptr);

	
	UAnimInstance* animInstance = _actionOwner->GetMesh()->GetAnimInstance();
	if (animInstance && montage== _aniMontage)
	{
		animInstance->OnMontageEnded.RemoveDynamic(this, &UActionDodge::OnAnimationFinished);
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("End Dodge animation"));

	character->SetCharacterState(ECharacterState::CS_GroundNormal);
	_state = EActionState::AS_SUCCEEDED;
}