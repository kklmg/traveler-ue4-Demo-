// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Event/EventBroker.h"
#include "Data/StateData.h"
#include "AnimControlComponent.generated.h"

class UAnimationModelBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UAnimControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimControlComponent();

	//animation model -----------------------------------------------------------------
	UAnimationModelBase* GetAnimationModel();

	//animation State ------------------------------------------------------------------

	UFUNCTION(BlueprintCallable)
	void SetAnimationState(EAnimationState newState);

	UFUNCTION(BlueprintCallable)
	EAnimationState GetAnimationState();

	FOnAnimationStateChanged& GetAnimationStateChangedDelegate();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UAnimationModelBase* _animationModelIns;

	UPROPERTY()
	ACharacter* _character;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAnimationModelBase> _animationModelClass;

	UPROPERTY()
	EAnimationState _animationState;

	UPROPERTY(EditDefaultsOnly,Category = animMontage)
	UAnimMontage* _montage;

	FOnAnimationStateChanged _animationStateChangedDelegate;
};
