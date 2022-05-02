// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ArrowData.h"
#include "GameSystem/OptionBase.h"
#include "QuiverComponent.generated.h"

class AArrowActorBase;
class UObjectPoolBase;


UCLASS(BlueprintType, Blueprintable)
class TRAVELER_API UArrowOption : public UOptionBase
{
	GENERATED_BODY()

public:
	virtual int32 VGetSize() override;
	UArrowData* GetSelection();

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UArrowData>> _options;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UQuiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitializeComponent() override;

public:	
	void SelectArrowOption(int32 id);
	void ScrollArrowOption(int32 ScrollAmount);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SpawnArrows(int count, APawn* instigator,TArray<AArrowActorBase*>& outArray);

private:
	UPROPERTY()
	UObjectPoolBase* _arrowPool;

	UPROPERTY(EditDefaultsOnly)
	int32 _poolSize;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AArrowActorBase> _arrowClass;

	UPROPERTY(EditDefaultsOnly, Category = ArrowClass)
	TSubclassOf<UArrowOption> _arrowOptionClass;

	UPROPERTY()
	UArrowOption* _arrowOptionIns;
};
