// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Event/EventBroker.h"
#include "Enums/EnumAnimation.h"
#include "AnimNotify/EnumAnimNotify.h"
#include "AnimControlComponent.generated.h"

class UAnimationModelBase;
class UAnimNotifier;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UAnimControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimControlComponent();

protected:
	virtual void InitializeComponent() override;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//animation model -----------------------------------------------------------------

	UFUNCTION(BlueprintCallable)
	UAnimationModelBase* GetAnimationModel();

	//animation State ------------------------------------------------------------------

	UFUNCTION(BlueprintCallable)
	void SetAnimationState(EAnimationState newState);

	UFUNCTION(BlueprintCallable)
	EAnimationState GetAnimationState();

	FOnAnimationStateChanged& GetAnimationStateChangedDelegate();

	//animation Notify ------------------------------------------------------------------

	void NotifyAnimStateBegin(EAnimNotifyKey notifyKey, float totalTime);
	void NotifyAnimStateTick(EAnimNotifyKey notifyKey, float frameDeltaTime);
	void NotifyAnimStateEnd(EAnimNotifyKey notifyKey);

	UAnimNotifier* GetNotifer(EAnimNotifyKey notifyKey);
	UAnimNotifier* GetOrCreateNotifer(EAnimNotifyKey notifyKey);

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

	UPROPERTY()
	TMap<EAnimNotifyKey, UAnimNotifier*> _mapNotifiers;

	FOnAnimationStateChanged _animationStateChangedDelegate;
};


