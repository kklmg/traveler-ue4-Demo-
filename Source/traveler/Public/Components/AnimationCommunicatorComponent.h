// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Event/EventBroker.h"
#include "Data/StateData.h"
#include "AnimationCommunicatorComponent.generated.h"

class UAnimationModelBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UAnimationCommunicatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimationCommunicatorComponent();

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

	UFUNCTION(BlueprintCallable)
	void PublishEvent(FName eventName, UEventDataBase* eventData);

	FOnEventPublished& GetEventDelegate(FName eventName);

private:
	UPROPERTY()
	UAnimationModelBase* _animationModelIns;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAnimationModelBase> _animationModelClass;

	UPROPERTY()
	UEventBroker* _eventBroker;

	UPROPERTY()
	EAnimationState _animationState;

	FOnAnimationStateChanged _animationStateChangedDelegate;
};
