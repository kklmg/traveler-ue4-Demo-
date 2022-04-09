// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/PoolableInterface.h"
#include "DamageWidget.generated.h"

USTRUCT(BlueprintType)
struct FDamageWidgetData
{
	GENERATED_USTRUCT_BODY()
public:
	FDamageWidgetData();

	FDamageWidgetData(FColor color);

	UPROPERTY(BlueprintReadOnly)
	float Damage;

	UPROPERTY(BlueprintReadOnly)
	FVector TextLocation;

	UPROPERTY(BlueprintReadOnly)
	FVector2D TextOffset;

	UPROPERTY(BlueprintReadOnly)
	float TextScale;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	FColor TextColor;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float ScrollSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FVector2D ScrollDirection;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	float Life;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	int32 ZOrder;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataUpdated);

/**
 * 
 */
UCLASS()
class TRAVELER_API UDamageWidget : public UUserWidget, public IPoolableInterface
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetData(FDamageWidgetData damageWidgetData);
	
	//PoolObject Interface implementation---------------------------------

	virtual bool VIsActive() override;
	virtual void VActivate() override;
	virtual void VInActivate() override;

	virtual int VGetPoolId()  override;
	virtual void VSetPoolId(int32 poolId)  override;
	virtual FOnObjectInactive& VGetObjectInactiveDelegate()  override;

public:
	UPROPERTY(BlueprintReadOnly)
	FDamageWidgetData DamageWidgetData;

	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime;

	UPROPERTY()
	FVector2D ScrollOffset;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FOnDataUpdated OnDataUpdated;

private:
	FOnObjectInactive _onObjectInActive;
	int32 _poolId;
	bool _bIsActive;
};
