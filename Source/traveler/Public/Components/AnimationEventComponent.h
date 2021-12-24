// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimNotify/AnimNotifyKey.h"
#include "AnimationEventComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnEnterAnimFrame);

USTRUCT()
struct FAnimNotifyDelegateData
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY()
	FOnEnterAnimFrame Delegate;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UAnimationEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimationEventComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void notify(EAnimNorifyKey notifyKey);

	template <typename UObjectTemplate, typename... VarTypes> 
	void Subscribe(EAnimNorifyKey notifyKey, UObjectTemplate objectTemplate, const FName& InFunctionName);

private:
	UPROPERTY()
	TMap<EAnimNorifyKey, FAnimNotifyDelegateData> _mapSubscribers;
		
};

template <typename UObjectTemplate, typename... VarTypes>
void UAnimationEventComponent::Subscribe(EAnimNorifyKey notifyKey, UObjectTemplate objectTemplate, const FName& InFunctionName)
{
	if (_mapSubscribers.Contains(notifyKey))
	{
		_mapSubscribers[notifyKey].Delegate.AddUFunction(objectTemplate, InFunctionName);
	}
}