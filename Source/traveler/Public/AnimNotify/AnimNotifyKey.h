// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify/EnumAnimNotify.h"
#include "AnimNotifyKey.generated.h"

class UAnimControlComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UAnimNotifyKey : public UAnimNotify
{
	GENERATED_BODY()
public:
	void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "key")
	EAnimNotifyKey NotifyKey;
private:
	UPROPERTY()
	UAnimControlComponent* _animControlComp;
};
