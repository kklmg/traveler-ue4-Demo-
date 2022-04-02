// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DebugMessageHelper.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UDebugMessageHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void Message_Int(FString Categoty, int32 value);
	static void Message_Float(FString Categoty, float value);
	static void Message_Vector(FString Categoty, FVector value);
	static void Messsage_Enum(FString Categoty, TCHAR* enumName,int32 enumValue);
	static void Messsage_String(FString Categoty, FString string);
};

