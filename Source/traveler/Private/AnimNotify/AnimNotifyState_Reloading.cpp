// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_Reloading.h"
#include "Character/MyCharacter.h"
#include "Components/WeaponComponent.h"
#include "Weapon/Weapon.h"


void UAnimNotifyState_Reloading::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) 
{


}
void UAnimNotifyState_Reloading::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) 
{

}
void UAnimNotifyState_Reloading::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
	AActor* actor = MeshComp->GetOwner();
	AMyCharacter* character = Cast<AMyCharacter>(actor);

	AWeapon* weapon = character->GetWeaponComponent()->GetEquipedWeapon();
	if (weapon != nullptr)
	{
		weapon->OnTickAnimFrame_Reloading();
	}
}