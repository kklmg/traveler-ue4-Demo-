// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionIdle.h"
#include "Character/MyCharacter.h"
#include "Components/AttributeComponent.h"


void UActionIdle::VBegin(AActor* actor, UActionData* actionData)
{
	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(actor);
	check(pCharacter != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	check(pAttributeComponent != nullptr);
	if (_AniMontage != nullptr)
	{
		pCharacter->PlayAnimMontage(_AniMontage);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Trigger Character Idle"));
	}
}

void UActionIdle::VUpdate(float deltaTime, AActor* actor, UActionData* actionData)
{
}