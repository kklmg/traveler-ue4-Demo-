// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/DebugMessageHelper.h"

void UDebugMessageHelper::Message_Int(FString Categoty, int32 value)
{
	Categoty.Append(FString::Printf(TEXT(": %d"), value));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, Categoty);
}

void UDebugMessageHelper::Message_Float(FString Categoty, float value)
{
	Categoty.Append(FString::Printf(TEXT(": %f"), value));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, Categoty);
}

void UDebugMessageHelper::Message_Vector(FString Categoty, FVector value)
{
	Categoty.Append(TEXT(": ") + value.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, Categoty);
}

void UDebugMessageHelper::Messsage_Enum(FString Categoty, TCHAR* enumName, int32 enumValue)
{
	Categoty.Append(TEXT(": "));
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, enumName, true);
	Categoty.Append( enumPtr ? enumPtr->GetNameStringByIndex(enumValue) : TEXT("UnKnown"));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, Categoty);
}