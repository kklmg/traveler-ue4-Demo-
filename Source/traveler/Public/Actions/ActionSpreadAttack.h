// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionWithAnimMontage.h"
#include "Data/EnumMeshSocketType.h"
#include "ActionSpreadAttack.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionSpreadAttack : public UActionWithAnimMontage
{
	GENERATED_BODY()
public:
	UActionSpreadAttack();

	virtual void VExecute() override;
	virtual void VTick(float deltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	EMeshSocketType _meshSocektType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> _effectClass;

	UPROPERTY(EditDefaultsOnly)
	AActor* _effect;

	FVector _shootDirection;

public:
	UFUNCTION()
	void OnAttackNotifyBegin(float durationTime);
	UFUNCTION()
	void OnAttackNotifyTick(float frameDeltaTime);
	UFUNCTION()
	void OnAttackNotifyEnd();
	

	void VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted) override;
};
