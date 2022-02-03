// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponent.generated.h"

class IActionInterface;
class IAttributeInterface;
class IAnimationModelProvider;

/**
 * 
 */
UCLASS()
class TRAVELER_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnCharacterWantToSprint(bool wantToSprint);

private:

	IActionInterface* _actionInterface;
	IAttributeInterface* _attributeInterface;
	IAnimationModelProvider* _animationModelProviderInterface;
};