// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyKey.generated.h"


UENUM(BlueprintType)
enum class EAnimNorifyKey : uint8
{
	ANK_StartSpreadAttack UMETA(DisplayName = "StartSpreadAttack"),
	ANK_StartMeleeAttack UMETA(DisplayName = "StartMeleeAttack"),
	ANK_StartSpitAttack UMETA(DisplayName = "StartSpitAttack"),
};



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
	EAnimNorifyKey NotifyKey;
};
