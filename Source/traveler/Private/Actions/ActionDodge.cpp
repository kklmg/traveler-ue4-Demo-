// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionDodge.h"
#include "Character/CreatureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/WeaponInterface.h"


UActionDodge::UActionDodge()
{
	_actionName = ActionName::DODGE;
	_actionType = EActionType::EACT_Dodge;
	_bInstantAction = false;
	_dodgeSpeed = 250;

	GetCostData()->AddCost(EStatusType::EStatus_Stamina,20);
	
}

bool UActionDodge::VTMCanExecute()
{
	EMovementMode movementMode = GetActionOwner()->GetCharacterMovement()->MovementMode;
	bool bIsWalking = (movementMode == EMovementMode::MOVE_Walking || movementMode == EMovementMode::MOVE_NavWalking);

	return bIsWalking;
}

void UActionDodge::VTMExecute()
{
	ACharacter* actionOwner = GetActionOwner();
	IWeaponInterface* weaponInterface = Cast<IWeaponInterface>(actionOwner);

	if(weaponInterface)
	{
		weaponInterface->VStopWeaponProcess(WeaponProcessName::AIM);
		weaponInterface->VStopWeaponProcess(WeaponProcessName::FIRE);
	}

	UAnimInstance* animInstance = actionOwner->GetMesh()->GetAnimInstance();
	if (_aniMontage && animInstance)
	{
		//bind 
		animInstance->OnMontageEnded.AddDynamic(this, &UActionDodge::OnAnimMontageFinished);

		//play montage
		actionOwner->PlayAnimMontage(_aniMontage);
	}

	_shiftDirection = actionOwner->GetVelocity().IsNearlyZero() ? 
						actionOwner->GetActorForwardVector() :  actionOwner->GetVelocity().GetSafeNormal();

	actionOwner->SetActorRotation(_shiftDirection.Rotation());
}

void UActionDodge::VTMTick(float deltaTime)
{
	Super::VTMTick(deltaTime);

	GetActionOwner()->AddMovementInput(_shiftDirection, _dodgeSpeed * deltaTime);
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