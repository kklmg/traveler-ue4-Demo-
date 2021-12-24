// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyKey.h"
#include "Character/CreatureCharacter.h"

void UAnimNotifyKey::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{

	Super::Notify(MeshComp, Animation);


	ACreatureCharacter* character = MeshComp->GetOwner<ACreatureCharacter>();
	if (character == nullptr) return;

	//character->animation

}
