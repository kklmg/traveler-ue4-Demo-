// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IKData.generated.h"

USTRUCT(BlueprintType)
struct FIKData 
{
	GENERATED_USTRUCT_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite)
	bool bImpact;
	UPROPERTY(BlueprintReadWrite)
	float Offset;
	UPROPERTY(BlueprintReadWrite)
	FVector Normal;
	UPROPERTY(BlueprintReadWrite)
	FRotator rotator;
};