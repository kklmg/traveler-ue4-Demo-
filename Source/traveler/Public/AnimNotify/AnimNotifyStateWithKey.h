// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotify/EnumAnimNotify.h"
#include "AnimNotifyStateWithKey.generated.h"

class UAnimControlComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UAnimNotifyStateWithKey : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "key")
	EAnimNotifyKeyType NotifyKey;

private:
	UPROPERTY()
	UAnimControlComponent* _animControlComp;
};
