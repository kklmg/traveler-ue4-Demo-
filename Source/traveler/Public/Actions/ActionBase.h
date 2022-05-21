// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Process/ProcessBase.h"
#include "Enums/EnumActionType.h"
#include "Enums/EnumProcessState.h"
#include "MyMacros.h"
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
class ICharacterCameraInterface;

namespace NSNameAction
{
	DECLARE_CONST_FNAME(Throw)
	DECLARE_CONST_FNAME(jump)
	DECLARE_CONST_FNAME(sprint)
	DECLARE_CONST_FNAME(dodge)
	DECLARE_CONST_FNAME(move)
	DECLARE_CONST_FNAME(idle)
	DECLARE_CONST_FNAME(aim)
	DECLARE_CONST_FNAME(ascend)
	DECLARE_CONST_FNAME(fly)
	DECLARE_CONST_FNAME(takeoff)
	DECLARE_CONST_FNAME(teleport)
	DECLARE_CONST_FNAME(FlyTo)
	DECLARE_CONST_FNAME(FlyAroundPoint)
	DECLARE_CONST_FNAME(WeaponFire)
	DECLARE_CONST_FNAME(WeaponAim)
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

	virtual void VSetUpActionData(ACharacter* character, UActionComponent* actionComp);

	UFUNCTION(BlueprintCallable)
	EActionType GetActionType();

	UFUNCTION(BlueprintCallable)
	ACharacter* GetActionOwner();

	UFUNCTION(BlueprintCallable)
	UActionBlackBoard* GetActionBlackBoard();

	UFUNCTION(BlueprintCallable)
	float GetElapsedTime();

protected:
	virtual void VOnInit() override;
	virtual void VOnExecute() override;
	virtual bool VCanExecute() override;
	virtual void VOnTick(float deltaTime) override;

	//virtual void VOnDead() override;
	//virtual void VOnSucceed() override;
	//virtual void VOnFailed() override;
	//virtual void VOnAborted() override;

protected:

	UActionComponent* GetActionComp();
	UAnimControlComponent* GetAnimControlComp();
	UCostData* GetCostData();
	UAnimationModelBase* GetAnimationViewModel();
	UStatusComponent* GetStatusComp();
	UExTransformProviderComponent* GetExTransformProviderComp();
	ICharacterCameraInterface *GetCameraInterface();

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
	UActionBlackBoard* _actionBlackBoard;

	UPROPERTY(EditDefaultsOnly)
	UCostData* _costData;

	UPROPERTY()
	UStatusComponent* _statusComp;
	UPROPERTY()
	UAnimControlComponent* _animControlComp;

	ICharacterCameraInterface* _cameraInterface;

	bool _bDataSettingIsFinished;
	float _elapsedTime;
};
