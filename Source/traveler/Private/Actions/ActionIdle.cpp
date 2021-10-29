// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionIdle.h"
#include "Character/MyCharacter.h"
#include "Components/AttributeComponent.h"

UActionIdle::UActionIdle() 
{
	_actionName = "Idle";
}


void UActionIdle::VBegin(AActor* actor, UActionData* actionData)
{
	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(actor);
	check(pCharacter != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	check(pAttributeComponent != nullptr);

	UAnimInstance* AnimInstance = pCharacter->GetMesh()->GetAnimInstance();

	UE_LOG(LogTemp,Log,TEXT("ani instance %s"),AnimInstance==nullptr?TEXT("no instance"):TEXT("exist instance"));

	if (_AniMontage != nullptr)
	{
		//pCharacter->PlayAnimMontage(_AniMontage);
		

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Trigger Character Idle"));
	}
}

void UActionIdle::VUpdate(float deltaTime, AActor* actor, UActionData* actionData)
{
}