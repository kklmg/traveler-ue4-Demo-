// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyState_TimedNiagaraEffect.h"
#include "AnimNotify/EnumAnimNotify.h"
#include "AnimNotifyStateWithKey_Niagara.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UAnimNotifyStateWithKey_Niagara : public UAnimNotifyState_TimedNiagaraEffect
{
	GENERATED_BODY()

	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "key")
	EAnimNorifyKey NotifyKey;
	
};
