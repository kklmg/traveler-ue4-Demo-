// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionSpreadAttack.h"
#include "GameFramework/Character.h"
#include "Character/CreatureCharacter.h"
#include "AnimNotify/AnimNotifyHandler.h"
#include "Components/AnimationEventComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "Actors/ThrowableActorBase.h"
#include "DrawDebugHelpers.h"

UActionSpreadAttack::UActionSpreadAttack()
{
	_actionName = ActionName::SPREADATTACK;
	_actionType = EActionType::EACT_SpreadAttack;
	_bInstantAction = false;
	_throwSpeed = 100;
}

void UActionSpreadAttack::VExecute()
{
	Super::VExecute();

	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;


	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();

	UAnimNotifyHandler* handler = animEventComp->GetHNotifyHandler(EAnimNorifyKey::ANK_SpreadAttack);
	handler->OnNotifyBegin.AddDynamic(this, &UActionSpreadAttack::OnAttackNotifyBegin);
	handler->OnNotifyTick.AddDynamic(this, &UActionSpreadAttack::OnAttackNotifyTick);
	handler->OnNotifyEnd.AddDynamic(this, &UActionSpreadAttack::OnAttackNotifyEnd);
}

void UActionSpreadAttack::VTick(float deltaTime)
{
	Super::VTick(deltaTime);

}

void UActionSpreadAttack::OnAttackNotifyBegin(float durationTime)
{
	if (GetWorld() == nullptr)	return;
	if (_throwableClass == nullptr) return;

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
	_throwableIns = GetWorld()->SpawnActor<AThrowableActorBase>(_throwableClass, outTransform, spawnParameters);


	//InitializeActor
	if (_throwableIns)
	{
		_throwableIns->SetSpawningTransform(outTransform);

		FVector outDirection= GetActionOwner()->GetActorForwardVector();
		_actionBlackBoard->TryGetData_FVector(EActionData::EACTD_Peojectile_FlyingDirection, outDirection);

		_actionBlackBoard->TryGetData_Float(EActionData::EACTD_Peojectile_FlyingSpeed, _throwSpeed);
		_throwableIns->VSetVelocity(outDirection * _throwSpeed + GetActionOwner()->GetVelocity());
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("make throwable actor instance failed"));
	}
}

void UActionSpreadAttack::OnAttackNotifyTick(float frameDeltaTime)
{
	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;

	FTransform outTransform;
	if (character->GetMeshSocketTransform(_meshSocektType, ERelativeTransformSpace::RTS_World, outTransform))
	{
		FTransform result;
		result.SetLocation(outTransform.GetLocation());

		FVector dir = character->GetActorForwardVector();
		result.SetRotation(dir.ToOrientationQuat());
		result.SetScale3D(outTransform.GetScale3D());

		if(_throwableIns)
		{
			_throwableIns->SetSpawningTransform(result);
		}
	}
}

void UActionSpreadAttack::OnAttackNotifyEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("attack notify End"));

	if(_throwableIns)
	{
		_throwableIns->Destroy();
		_throwableIns = nullptr;
	}
}


void UActionSpreadAttack::VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted)
{
	Super::VOnAnimMontageFinished(montage, interrupted);

	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;

	UAnimationEventComponent* animEventComp = character->GetAanimationEventComponent();

	UAnimNotifyHandler* handler = animEventComp->GetHNotifyHandler(EAnimNorifyKey::ANK_SpreadAttack);

	handler->OnNotifyBegin.RemoveDynamic(this, &UActionSpreadAttack::OnAttackNotifyBegin);
	handler->OnNotifyTick.RemoveDynamic(this, &UActionSpreadAttack::OnAttackNotifyTick);
	handler->OnNotifyEnd.RemoveDynamic(this, &UActionSpreadAttack::OnAttackNotifyEnd);
}

