// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ActionWithAnimMontage.h"
#include "Enums/EnumTransformType.h"
#include "ActionShoot.generated.h"

class AProjectileActorBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionShoot : public UActionWithAnimMontage
{
	GENERATED_BODY()
public:
	UActionShoot();

	virtual bool VCanExecute() override;
	virtual void VOnExecute() override;
	virtual void VOnTick(float deltaTime) override;
	virtual void VOnDead() override;

private:
	UPROPERTY(EditDefaultsOnly)
	ETransformType _transformType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileActorBase> _projectileClass;

	UPROPERTY(EditDefaultsOnly)
	float _shootingSpeed;

	FVector _targetLocation;

public:
	UFUNCTION()
	void OnAttackNotifyBegin(float durationTime);
};
