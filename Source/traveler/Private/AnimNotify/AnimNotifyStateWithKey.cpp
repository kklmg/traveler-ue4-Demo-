// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyStateWithKey.h"
#include "Character/CreatureCharacter.h"
#include "Components/AnimControlComponent.h"


void UAnimNotifyStateWithKey::NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	AActor* actor = MeshComp->GetOwner();
	if (!actor) return;

	_animControlComp = Cast<UAnimControlComponent>(actor->GetComponentByClass(UAnimControlComponent::StaticClass()));
	if (_animControlComp)
	{
		_animControlComp->NotifyAnimStateBegin(NotifyKey,TotalDuration);
	}
}

void UAnimNotifyStateWithKey::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (_animControlComp)
	{
		_animControlComp->NotifyAnimStateTick(NotifyKey, FrameDeltaTime);
	}
}

void UAnimNotifyStateWithKey::NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (_animControlComp)
	{
		_animControlComp->NotifyAnimStateEnd(NotifyKey);
	}
}

