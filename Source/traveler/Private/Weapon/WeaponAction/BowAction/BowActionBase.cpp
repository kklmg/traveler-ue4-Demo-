// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponAction/BowAction/BowActionBase.h"
#include "Components/ActionComponent.h"
#include "Enums/EnumAnimation.h"
#include "Components/AnimControlComponent.h"
#include "Components/WeaponComponent.h"


void UBowActionBase::VSetUpActionData(ACharacter* character, UActionComponent* actionComp)
{
	Super::VSetUpActionData(character, actionComp);
	if(GetWeaponComp())
	{
		_bow = Cast<ABowBase>(GetWeaponComp()->GetEquipedWeapon());
	}
}

bool UBowActionBase::VCanExecute()
{
	if (!Super::VCanExecute()) return false;
	if (!_bow) return false;
	if (!GetAnimControlComp()) return false;
	if (GetActionComp()->IsActionAlive(EActionType::EACT_Dodge)) return false;

	EAnimationState animationState = GetAnimControlComp()->GetAnimationState();
	return (animationState == EAnimationState::EAnimState_Walk || animationState == EAnimationState::EAnimState_Fall);
}

void UBowActionBase::VOnExecute()
{
	Super::VOnExecute();

}

FORCEINLINE_DEBUGGABLE ABowBase* UBowActionBase::GetBow()
{
	return _bow;
}
