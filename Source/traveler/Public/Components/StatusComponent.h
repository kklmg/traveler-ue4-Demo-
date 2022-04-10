// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Status/EnumStatus.h"
#include "StatusComponent.generated.h"

class UDataTable;
class UStatusBase;
class UBasicStatus;
class UCostData;
class UBasicStatus;
class UAnimationModelBase;
class ULevelStatus;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetLevelValue();
	ULevelStatus* GetLevelStatusIns();

	float GetPrimaryValue(EStatusType statusType);
	float GetBasicValue(EStatusType statusType);
	float GetFinalValue(EStatusType statusType);
	float GetRemainingValue(EStatusType statusType);

	UFUNCTION(BlueprintCallable)
	UStatusBase* GetStatusIns(EStatusType statusType);
	UFUNCTION(BlueprintCallable)
	UBasicStatus* GetBasicStatusIns(EStatusType statusType);

	void ApplyRemainingValueChange(EStatusType statusType, float value);
	bool IsRemainingValueEnough(UCostData* costData);
	bool ApplyCost(UCostData* costData);

private:
	void InitializeStatusData();

	UPROPERTY(EditDefaultsOnly, Category = Status)
	int32 _defaultLevel;
	UPROPERTY(EditDefaultsOnly, Category = Status)
	UDataTable* _statusTable;
	UPROPERTY()
	ULevelStatus* _levelStatusIns;
	UPROPERTY()
	UAnimationModelBase* _animationViewModel;
	UPROPERTY()
	TMap<EStatusType, UStatusBase*> _statusMap;
	UPROPERTY()
	TMap<EStatusType, UBasicStatus*> _basicStatusMap;
};