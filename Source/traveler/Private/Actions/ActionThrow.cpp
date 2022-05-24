// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionThrow.h"
#include "GameFramework/Character.h"
#include "Character/CreatureCharacter.h"
#include "AnimNotify/AnimNotifier.h"
#include "Components/AnimControlComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actors/ThrowerActorBase.h"
#include "DrawDebugHelpers.h"

UActionThrow::UActionThrow()
{
	_processName = NSNameAction::Throw;
	_actionType = EActionType::EACT_Throw;
	_bIsInstantProcess = false;
	_throwingSpeed = 100;
}

void UActionThrow::VOnExecute()
{
	Super::VOnExecute();

	if (GetAnimControlComp())
	{
		UAnimNotifier* notifier = GetAnimControlComp()->GetOrCreateNotifer(EAnimNotifyKey::ANK_SpreadAttack);
		notifier->NotifyBeginDelegate.AddDynamic(this, &UActionThrow::OnAttackNotifyBegin);
		notifier->NotifyTickDelegate.AddDynamic(this, &UActionThrow::OnAttackNotifyTick);
		notifier->NotifyEndDelegate.AddDynamic(this, &UActionThrow::OnAttackNotifyEnd);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("bind delegates")));
	}
	else
	{
		SetProcessFailed();
	}
}

void UActionThrow::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);
}

void UActionThrow::VOnDead()
{
	Super::VOnDead();

	if (GetAnimControlComp())
	{
		UAnimNotifier* notifier = GetAnimControlComp()->GetOrCreateNotifer(EAnimNotifyKey::ANK_SpreadAttack);

		notifier->NotifyBeginDelegate.RemoveDynamic(this, &UActionThrow::OnAttackNotifyBegin);
		notifier->NotifyTickDelegate.RemoveDynamic(this, &UActionThrow::OnAttackNotifyTick);
		notifier->NotifyEndDelegate.RemoveDynamic(this, &UActionThrow::OnAttackNotifyEnd);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("unBind delegates")));

	}
	if (_throwerIns)
	{
		_throwerIns->VStartThrowing();
		_throwerIns->MarkDestroy();
		_throwerIns = nullptr;
	}
}

void UActionThrow::OnAttackNotifyBegin(float durationTime)
{
	if (_throwerClass == nullptr) return;

	//set spawn options
	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetActionOwner();
	spawnParameters.Owner = GetActionOwner();

	FTransform outTransform;
	FName outSocketName;

	if (GetExTransformProviderComp())
	{
		GetExTransformProviderComp()->TryGetTransform(_transformType, ERelativeTransformSpace::RTS_World, outTransform);
		GetExTransformProviderComp()->TryGetSocketName(_transformType, outSocketName);
	}

	//spawn actor
	_throwerIns = GetWorld()->SpawnActor<AThrowerActorBase>(_throwerClass, outTransform, spawnParameters);
	_throwerIns->AttachToComponent(GetActionOwner()->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, outSocketName);
	
	//
	_throwerIns->VStartThrowing();
}

void UActionThrow::OnAttackNotifyTick(float frameDeltaTime)
{
	if (GetActionOwner() == nullptr) return;

	//IExtraTransformProvider* meshSocketTransformProvider = Cast<IExtraTransformProvider>(GetActionOwner());
	//if (meshSocketTransformProvider == nullptr) return;

	//FTransform outTransform;
	/*if (meshSocketTransformProvider->VTryGetTransform(_transformType, ERelativeTransformSpace::RTS_World, outTransform))
	{
		if(_throwerIns)
		{
			_throwerIns->VSetSpawningLocation(outTransform.GetLocation());
			_throwerIns->VSetThrowingDirection(outTransform.GetRotation().Vector());
		}
	}*/
}

void UActionThrow::OnAttackNotifyEnd()
{
	if (_throwerIns)
	{
		_throwerIns->VStartThrowing();
		_throwerIns->MarkDestroy();
		_throwerIns = nullptr;
	}
}