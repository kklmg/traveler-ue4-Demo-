// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionShoot.h"
#include "Actors/ProjectileActorBase.h"
#include "GameFramework/Character.h"
#include "Character/CreatureCharacter.h"
#include "AnimNotify/AnimNotifier.h"
#include "Components/AnimControlComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actors/ThrowerActorBase.h"
#include "DrawDebugHelpers.h"
#include "Data/AnimationModelBase.h"

UActionShoot::UActionShoot()
{
	_processName = NSNameAction::Shoot;
	_actionType = EActionType::EACT_Shoot;
	_animMontageType = EAnimMontageKey::EAnimMontage_Shoot;

	_shootingSpeed = 2000.0f;
	_targetLocation = FVector::ForwardVector;
}

bool UActionShoot::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	if (_projectileClass == nullptr)
	{
		UE_LOG(LogAction, Warning, TEXT("UActionShoot: No ProjectileClass"));
		return false;
	}

	return true;
}

void UActionShoot::VOnExecute()
{
	Super::VOnExecute();

	if (GetAnimControlComp())
	{
		UAnimNotifier* notifier = GetAnimControlComp()->GetOrCreateNotifer(EAnimNotifyKeyType::ANK_ShootAttack);
		notifier->NotifyBeginDelegate.AddDynamic(this, &UActionShoot::OnAttackNotifyBegin);

		GetAnimControlComp()->GetAnimViewModel()->SetBool(NSAnimationDataKey::bToggleNeckIK, true);
	}
	GetActionBlackBoard()->TryGetData_FVector(NSActionData::ShootingTargetLocation::Name, _targetLocation);
	GetActionBlackBoard()->TryGetData_Float(NSActionData::ShootingDirection::Name, _shootingSpeed);
}

void UActionShoot::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	GetActionBlackBoard()->TryGetData_FVector(NSActionData::ShootingTargetLocation::Name, _targetLocation);
	if (GetAnimControlComp())
	{
		GetAnimControlComp()->GetAnimViewModel()->SetVector(NSAnimationDataKey::vShootingTargetLocation, _targetLocation);
		GetAnimControlComp()->GetAnimViewModel()->SetBool(NSAnimationDataKey::bToggleNeckIK, false);
	}
}

void UActionShoot::VOnDead()
{
	Super::VOnDead();

	if(GetAnimControlComp())
	{
		UAnimNotifier* notifier = GetAnimControlComp()->GetOrCreateNotifer(EAnimNotifyKeyType::ANK_ShootAttack);
		notifier->NotifyBeginDelegate.RemoveDynamic(this, &UActionShoot::OnAttackNotifyBegin);
	}
}

void UActionShoot::OnAttackNotifyBegin(float durationTime)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = GetActionOwner();
	spawnParams.Owner = GetActionOwner();
	
	//get shooting location
	FTransform outTransform;
	if (GetExTransformProviderComp())
	{
		GetExTransformProviderComp()->TryGetTransform(ETransformType::ETransform_Mouth, ERelativeTransformSpace::RTS_World, outTransform);
	}
	
	//get shooting direction
	FVector shootingDirection = (_targetLocation - outTransform.GetLocation()).GetSafeNormal();

	//spawn projectile
	AProjectileActorBase* projectileIns = GetWorld()->SpawnActor<AProjectileActorBase>(_projectileClass,outTransform, spawnParams);
	projectileIns->VSetVelocity(shootingDirection * _shootingSpeed);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("shoot notify!"));
}
