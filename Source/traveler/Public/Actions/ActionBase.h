// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumProcessState.h"
#include "ActionBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAction, Log, All);

class UCostData;
class UActionComponent;
class UStatusComponent;
class UWeaponComponent;
class UActionBlackBoard;
class UAnimationModelBase;
class UAnimControlComponent;
class UExTransformProviderComponent;


namespace NSNameAction
{
	const FName Throw = FName(TEXT("Throw"));
	const FName JUMP = FName(TEXT("jump"));
	const FName SPRINT = FName(TEXT("sprint"));
	const FName DODGE = FName(TEXT("dodge"));
	const FName MOVE = FName(TEXT("move"));
	const FName IDLE = FName(TEXT("idle"));
	const FName AIM = FName(TEXT("aim"));
	const FName ASCEND = FName(TEXT("ascend"));
	const FName FLY = FName(TEXT("fly"));
	const FName TAKEOFF = FName(TEXT("takeoff"));
	const FName TELEPORT = FName(TEXT("teleport"));
	const FName FlyTo = FName(TEXT("FlyTo"));
	const FName WeaponFire = FName(TEXT("WeaponFire"));
	const FName WeaponAim = FName(TEXT("WeaponAim"));
}

/**
 *
 */
UCLASS(Blueprintable)
class TRAVELER_API UActionBase : public UProcessBase
{
	GENERATED_BODY()
public:
	UActionBase();

	void SetActionData(ACharacter* character, UActionComponent* actionComp, UActionBlackBoard* actionBlackBoard);

	UFUNCTION(BlueprintCallable)
	EActionType GetActionType();

	UFUNCTION(BlueprintCallable)
	ACharacter* GetActionOwner();

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* GetActionBlackBoard();

	UFUNCTION(BlueprintCallable)
	float GetElapsedTime();

protected:
	virtual void VTMInit() override;
	virtual void VTMExecute() override;
	virtual bool VTMCanExecute() override;
	virtual void VTMTick(float deltaTime) override;

protected:

	UActionComponent* GetActionComp();
	UAnimControlComponent* GetAnimControlComp();
	UCostData* GetCostData();
	UAnimationModelBase* GetAnimationViewModel();
	UWeaponComponent* GetWeaponComp();
	UStatusComponent* GetStatusComp();
	UExTransformProviderComponent* GetExTransformProviderComp();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	EActionType _actionType;

private:
	UPROPERTY()
	ACharacter* _actionOwner;

	UPROPERTY()
	UActionComponent* _actionComp;

	UPROPERTY()
	UExTransformProviderComponent* _exTransformProviderComp;

	UPROPERTY()
	UWeaponComponent* _weaponComp;

	UPROPERTY()
	UActionBlackBoard* _actionBlackBoard;

	UPROPERTY(EditDefaultsOnly)
	UCostData* _costData;

	UPROPERTY()
	UStatusComponent* _statusComp;
	UPROPERTY()
	UAnimControlComponent* _animControlComp;

	float _elapsedTime;
};
