// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyStateWithKey.h"
#include "Character/CreatureCharacter.h"
#include "Components/AnimationEventComponent.h"


void UAnimNotifyStateWithKey::NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACreatureCharacter* character = MeshComp->GetOwner<ACreatureCharacter>();
	if (character == nullptr) return;

	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();
	if (animEventComp == nullptr) return;

	animEventComp->notifyBegin(NotifyKey, TotalDuration);
}

void UAnimNotifyStateWithKey::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	ACreatureCharacter* character = MeshComp->GetOwner<ACreatureCharacter>();
	if (character == nullptr) return;

	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();
	if (animEventComp == nullptr) return;

	animEventComp->notifyTick(NotifyKey, FrameDeltaTime);

}

void UAnimNotifyStateWithKey::NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACreatureCharacter* character = MeshComp->GetOwner<ACreatureCharacter>();
	if (character == nullptr) return;

	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();
	if (animEventComp == nullptr) return;

	animEventComp->notifyEnd(NotifyKey);
}
