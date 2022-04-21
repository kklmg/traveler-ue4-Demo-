// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EnumActionType.h"
#include "Data/EnumProcessState.h"
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


namespace ActionName
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
class TRAVELER_API UActionBase : public UObject
{
	GENERATED_BODY()
public:
	UActionBase();

	virtual void VInitialize(ACharacter* character, UActionComponent* actionComp, UActionBlackBoard* actionBlackBoard);

	UFUNCTION(BlueprintCallable)
	void Execute();
	UFUNCTION(BlueprintCallable)
	bool CanExecute();
	UFUNCTION()
	void Tick(float deltaTime);

	UFUNCTION(BlueprintCallable)
	void Pause();

	UFUNCTION(BlueprintCallable)
	void Abort();

	UFUNCTION(BlueprintCallable)
	bool IsInstantAction();

	UFUNCTION(BlueprintCallable)
	FName GetActionName();

	UFUNCTION(BlueprintCallable)
	EActionType GetActionType();

	UFUNCTION(BlueprintCallable)
	bool IsCompleted();

	UFUNCTION(BlueprintCallable)
	EProcessState GetActionProcessState();

	UFUNCTION(BlueprintCallable)
	ACharacter* GetActionOwner();

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* GetActionBlackBoard();

	UFUNCTION(BlueprintCallable)
	float GetElapsedTime();

protected:

	virtual bool VTMCanExecute();
	virtual void VTMExecute();
	virtual void VTMTick(float deltaTime);
	virtual void VOnActionCompleted();

protected:
	void SetActionProcessSucceed();
	void SetActionProcessFailed();

	UActionComponent* GetActionComp();
	UAnimControlComponent* GetAnimControlComp();
	UCostData* GetCostData();
	UAnimationModelBase* GetAnimationViewModel();
	UWeaponComponent* GetWeaponComp();
	UStatusComponent* GetStatusComp();
	UExTransformProviderComponent* GetExTransformProviderComp();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName _actionName;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	EActionType _actionType;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool _bInstantAction;

	

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

	UPROPERTY(VisibleAnywhere, Category = "Action")
	EProcessState _processState;

	UPROPERTY(EditDefaultsOnly)
	UCostData* _costData;

	UPROPERTY()
	UStatusComponent* _statusComp;
	UPROPERTY()
	UAnimControlComponent* _animControlComp;

	float _elapsedTime;
};
