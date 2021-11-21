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
	AActor* actor = MeshComp->GetOwner();
	if (actor == nullptr) 
	{
		return;
	}
	AMyCharacter* character = Cast<AMyCharacter>(actor);
	if (character == nullptr) 
	{
		return;
	}

	AWeapon* weapon = character->GetEquippedWeapon();
	if (weapon == nullptr)
	{
		return;
	}

	weapon->OnTickAnimFrame_Reloading();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("notify Tick"));
}
void UAnimNotifyState_Reloading::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
	
}