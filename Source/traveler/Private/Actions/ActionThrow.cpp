// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionThrow.h"
#include "GameFramework/Character.h"
#include "Character/CreatureCharacter.h"
#include "AnimNotify/AnimNotifyHandler.h"
#include "Components/AnimationEventComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actors/ThrowerActorBase.h"
#include "DrawDebugHelpers.h"

UActionThrow::UActionThrow()
{
	_actionName = ActionName::Throw;
	_actionType = EActionType::EACT_Throw;
	_bInstantAction = false;
	_throwingSpeed = 100;
}

void UActionThrow::VExecute()
{
	Super::VExecute();


	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;


	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();

	UAnimNotifyHandler* handler = animEventComp->GetHNotifyHandler(EAnimNorifyKey::ANK_SpreadAttack);
	handler->OnNotifyBegin.AddDynamic(this, &UActionThrow::OnAttackNotifyBegin);
	handler->OnNotifyTick.AddDynamic(this, &UActionThrow::OnAttackNotifyTick);
	handler->OnNotifyEnd.AddDynamic(this, &UActionThrow::OnAttackNotifyEnd);
}

void UActionThrow::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

}

void UActionThrow::OnAttackNotifyBegin(float durationTime)
{
	if (GetWorld() == nullptr)	return;
	if (_throwerClass == nullptr) return;

	AActor* actionOwner = GetActionOwner();
	if (actionOwner == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(actionOwner);
	if (character == nullptr) return;

	//set spawn options
	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = character;
	spawnParameters.Owner = character;
	
	FTransform outTransform;
	character->GetMeshSocketTransform(_meshSocektType, ERelativeTransformSpace::RTS_World, outTransform);

	//spawn actor
	_throwerIns = GetWorld()->SpawnActor<AThrowerActorBase>(_throwerClass, outTransform, spawnParameters);


	//Initialize Actor
	if (_throwerIns)
	{
		_throwerIns->VSetSpawningLocation(outTransform.GetLocation());

		FVector outDirection= GetActionOwner()->GetActorForwardVector();
		_actionBlackBoard->TryGetData_FVector(EActionData::EACTD_Peojectile_FlyingDirection, outDirection);

		_actionBlackBoard->TryGetData_Float(EActionData::EACTD_Peojectile_FlyingSpeed, _throwingSpeed);
		_throwerIns->VSetSpeed(_throwingSpeed + GetActionOwner()->GetVelocity().Size());
		_throwerIns->VSetThrowingDirection(outTransform.GetRotation().Vector());
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("make throwable actor instance failed"));
	}
}

void UActionThrow::OnAttackNotifyTick(float frameDeltaTime)
{
	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;

	FTransform outTransform;
	if (character->GetMeshSocketTransform(_meshSocektType, ERelativeTransformSpace::RTS_World, outTransform))
	{
		if(_throwerIns)
		{
			_throwerIns->VSetSpawningLocation(outTransform.GetLocation());
			_throwerIns->VSetThrowingDirection(outTransform.GetRotation().Vector());
		}
	}
}

void UActionThrow::OnAttackNotifyEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("attack notify End"));

	if(_throwerIns)
	{
		_throwerIns->Destroy();
		_throwerIns = nullptr;
	}
}


void UActionThrow::VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted)
{
	Super::VOnAnimMontageFinished(montage, interrupted);

	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;

	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();

	UAnimNotifyHandler* handler = animEventComp->GetHNotifyHandler(EAnimNorifyKey::ANK_SpreadAttack);

	handler->OnNotifyBegin.RemoveDynamic(this, &UActionThrow::OnAttackNotifyBegin);
	handler->OnNotifyTick.RemoveDynamic(this, &UActionThrow::OnAttackNotifyTick);
	handler->OnNotifyEnd.RemoveDynamic(this, &UActionThrow::OnAttackNotifyEnd);
}
