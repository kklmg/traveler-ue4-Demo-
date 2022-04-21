// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionWithAnimMontage.h"
#include "Enums/EnumTransformType.h"
#include "ActionThrow.generated.h"

class AThrowerActorBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionThrow : public UActionWithAnimMontage
{
	GENERATED_BODY()
public:
	UActionThrow();

	virtual void VTMExecute() override;
	virtual void VTMTick(float deltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	ETransform _transformType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AThrowerActorBase> _throwerClass;

	UPROPERTY()
	AThrowerActorBase* _throwerIns;

	UPROPERTY(EditDefaultsOnly)
	float _throwingSpeed;

public:
	UFUNCTION()
	void OnAttackNotifyBegin(float durationTime);
	UFUNCTION()
	void OnAttackNotifyTick(float frameDeltaTime);
	UFUNCTION()
	void OnAttackNotifyEnd();
	

	void VOnAnimMontageFinished(UAnimMontage* montage, bool interrupted) override;
};
