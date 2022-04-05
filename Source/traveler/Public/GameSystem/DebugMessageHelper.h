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
	static void Message_Int(FString Categoty, int32 value, float timeToDisplay = 5.0f);
	static void Message_Float(FString Categoty, float value, float timeToDisplay = 5.0f);
	static void Message_Vector(FString Categoty, FVector valu, float timeToDisplay = 5.0f);
	static void Messsage_Enum(FString Categoty, TCHAR* enumName,int32 enumValue, float timeToDisplay = 5.0f);
	static void Messsage_String(FString Categoty, FString string, float timeToDisplay = 5.0f);
};

