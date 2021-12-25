// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionSpreadAttack.h"
#include "GameFramework/Character.h"
#include "Character/CreatureCharacter.h"
#include "Components/AnimationEventComponent.h"

UActionSpreadAttack::UActionSpreadAttack()
{
	_actionName = ActionName::SPREADATTACK;
	_bInstantAction = false;
}

void UActionSpreadAttack::VExecute()
{
	Super::VExecute();

	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if(character == nullptr) return;

	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();
	animEventComp->Subscribe(EAnimNorifyKey::ANK_StartSpreadAttack, this, FName("OnEnterAniFrameAttack"));

}

void UActionSpreadAttack::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

}

void UActionSpreadAttack::OnEnterAniFrameAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("enter frame attack"));

}

void UActionSpreadAttack::VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted)
{
	Super::VOnAnimMontageFinished(montage, interrupted);


	//animEventComp->Subscribe(EAnimNorifyKey::ANK_StartSpreadAttack, this, FName("OnEnterAniFrameAttack"));




}

