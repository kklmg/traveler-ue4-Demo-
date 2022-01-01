// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumActionType.h"
#include "ActionBlackBoard.generated.h"

class UActionDataBase;

/**
 * 
 */
UCLASS()
class TRAVELER_API UActionBlackBoard : public UObject
{
	GENERATED_BODY()
//public:
//	template<typename T>
//	static T* MakeActionData();

public:
	UFUNCTION(BlueprintCallable)
	void WriteData_Int(EActionData key, int value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Float(EActionData key, float value);

	UFUNCTION(BlueprintCallable)
	void WriteData_FVector(EActionData key, FVector value);

	UFUNCTION(BlueprintCallable)
	void WriteData_UObject(EActionData key, UObject* value);

public:
	UActionDataBase* GetData(EActionData key);

	template<typename T>
	T* GetData(EActionData key);

	template<typename T>
	T* GetOrCreateData(EActionData key);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Int(EActionData key, int& outValue);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Float(EActionData key, float& outValue);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_FVector(EActionData key, FVector& outValue);

	//UFUNCTION()
	bool TryGetData_UObject(EActionData key, UObject** outValue);

private:
	TMap<EActionData, UActionDataBase*> _mapActionData;
};

template<typename T>
T* UActionBlackBoard::GetData(EActionData key)
{
	UActionDataBase* data = GetData(key);
	T* result = nullptr;
	if(data)
	{
		result = Cast<T>(data);
	}
	return result;
}

template<typename T>
T* UActionBlackBoard::GetOrCreateData(EActionData key)
{
	T* data = GetData<T>(key);

	if (data == nullptr)
	{
		data = NewObject<T>();
		if(data)
		{
			this->_mapActionData.Add(key, data);
		}
	}
	return data;
}

//template<typename T>
//static T* UActionBlackBoard::MakeActionData()
//{
//	T* dataIns = NewObject<T>();
//	return T;
//}
//
