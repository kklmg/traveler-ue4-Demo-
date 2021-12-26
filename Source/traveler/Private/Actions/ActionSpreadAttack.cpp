// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionSpreadAttack.h"
#include "GameFramework/Character.h"
#include "Character/CreatureCharacter.h"
#include "AnimNotify/AnimNotifyHandler.h"
#include "Components/AnimationEventComponent.h"
#include "DrawDebugHelpers.h"

UActionSpreadAttack::UActionSpreadAttack()
{
	_actionName = ActionName::SPREADATTACK;
	_bInstantAction = false;
	_spreadDistance = 1000;
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
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("attack notify Begin"));

}

void UActionSpreadAttack::OnAttackNotifyTick(float frameDeltaTime)
{
	if (GetActionOwner() == nullptr) return;

	ACreatureCharacter* character = Cast<ACreatureCharacter>(GetActionOwner());
	if (character == nullptr) return;

	FTransform outTransform;
	if (character->GetMeshSocketTransform(_meshSocektType, ERelativeTransformSpace::RTS_World, outTransform))
	{
		FVector launchLocation = outTransform.GetLocation();
		FVector launchDir = outTransform.GetRotation().RotateVector(FVector::ForwardVector);

		//do line tracing
		FHitResult hitResult;
		FCollisionQueryParams CollisionParams;
		FVector hitLocation = launchLocation + launchDir * _spreadDistance;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, launchLocation, launchLocation + launchDir * _spreadDistance, ECC_Visibility, CollisionParams))
		{
			hitLocation = hitResult.ImpactPoint;
		
		}
		DrawDebugLine(GetWorld(), launchLocation, hitLocation, FColor::Red, false, -1.0f, 0U, 30.0f);
	}
}

void UActionSpreadAttack::OnAttackNotifyEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("attack notify End"));
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

