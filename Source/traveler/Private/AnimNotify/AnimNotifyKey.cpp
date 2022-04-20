// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyKey.h"
#include "Character/CreatureCharacter.h"
#include "Components/AnimControlComponent.h"

void UAnimNotifyKey::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AActor* actor = MeshComp->GetOwner();
	if (!actor) return;

	_animControlComp = Cast<UAnimControlComponent>(actor->GetComponentByClass(UAnimControlComponent::StaticClass()));
	if (_animControlComp)
	{
		_animControlComp->NotifyAnimStateBegin(NotifyKey, 0);
	}
}
