// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Templates/Tuple.h"
#include "Materials/Material.h"
#include "ObjectData.generated.h"

/**
 * 
 */

UCLASS()
class TRAVELER_API UDataBool : public UObject
{
	GENERATED_BODY()
public:
	bool Value;
};

UCLASS()
class TRAVELER_API UDataUInt8 : public UObject
{
	GENERATED_BODY()
public:
	uint8 Value;
};



UCLASS()
class TRAVELER_API UDataInt32 : public UObject
{
	GENERATED_BODY()
public:
	int32 Value;
};


UCLASS()
class TRAVELER_API UDataFloat : public UObject
{
	GENERATED_BODY()
public:
	float Value;
};

UCLASS()
class TRAVELER_API UDataVector : public UObject
{
	GENERATED_BODY()
public:
	FVector Value;
};

UCLASS()
class TRAVELER_API UDataQuat : public UObject
{
	GENERATED_BODY()
public:
	FQuat Value;
};



USTRUCT(BlueprintType)
struct FPairKey_Int32
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName key;

	UPROPERTY(EditAnywhere)
	int32 Value;
};

USTRUCT(BlueprintType)
struct FPairKey_Float
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName key;

	UPROPERTY(EditAnywhere)
	float Value;
};

USTRUCT(BlueprintType)
struct FPairKey_Vector
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName key;

	UPROPERTY(EditAnywhere)
	FVector Value;
};

USTRUCT(BlueprintType)
struct FPairKey_Quat
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName key;

	UPROPERTY(EditAnywhere)
	FQuat Value;
};


USTRUCT(BlueprintType)
struct TRAVELER_API FCompositeData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FPairKey_Int32> Data_Int32;

	UPROPERTY(EditAnywhere)
	TArray<FPairKey_Float> Data_Float;

	UPROPERTY(EditAnywhere)
	TArray<FPairKey_Float> Data_Vector;

	UPROPERTY(EditAnywhere)
	TArray<FPairKey_Float> Data_Quat;
};