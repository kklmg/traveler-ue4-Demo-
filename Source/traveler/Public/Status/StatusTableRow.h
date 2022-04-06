// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Status/EnumStatus.h"
#include "StatusTableRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStatusTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	FName LocaleKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	EStatusType StatusType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	float Growth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	float Recovery;

	bool IsBasicStatus();
};
