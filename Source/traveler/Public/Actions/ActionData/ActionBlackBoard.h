// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums/EnumActionType.h"
#include "Data/MyDelegates.h"
#include "Data/ObjectData.h"
#include "ActionBlackBoard.generated.h"

class UActionDataBase;

UCLASS(Blueprintable)
class TRAVELER_API UActionBlackBoard : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void WriteData_Bool(FName key, bool value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Int32(FName key, int32 value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Float(FName key, float value);

	UFUNCTION(BlueprintCallable)
	void WriteData_FVector(FName key, FVector value);

	UFUNCTION(BlueprintCallable)
	void WriteData_UObject(FName key, UObject* value);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Bool(FName key, bool& outValue,bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Int32(FName key, int32& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Float(FName key, float& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_FVector(FName key, FVector& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	UObject* GetData_UObject(FName key, bool bConsumeData = false);

	template<typename TUObject>
	TUObject* GetDataAs(FName key);

	template<typename TUObject>
	FDelegateHandle Subscribe(FName key, TUObject* inUserObj, void (TUObject::* InFunc)(UObject*));

	void DeleteData(FName key);

protected:
	void NotifyData(FName key);

	template<typename TUObject>
	TUObject* GetOrCreateDataAs(FName key);

private:
	UPROPERTY()
	TMap<FName, UObject*> _mapData;
	TMap<FName, FMD_UObjectSignature> _mapDataDelegates;
};

template<typename TUObject>
TUObject* UActionBlackBoard::GetDataAs(FName key)
{
	if (_mapData.Contains(key))
	{
		return Cast<TUObject>(_mapData[key]);
	}
	else
	{
		return nullptr;
	}
}

template<typename TUObject>
TUObject* UActionBlackBoard::GetOrCreateDataAs(FName key)
{
	if (_mapData.Contains(key))
	{
		return Cast<TUObject>(_mapData[key]);
	}
	else
	{
		TUObject* newData = NewObject<TUObject>(this);
		_mapData.Add(key, newData);
		return newData;
	}
}

template<typename TUObject>
FDelegateHandle UActionBlackBoard::Subscribe(FName key, TUObject* inUserObj, void (TUObject::* InFunc)(UObject*))
{
	if (_mapDataDelegates.Contains(key))
	{
		_mapDataDelegates.Add(key,FMD_UObjectSignature());
	}
	return 	_mapDataDelegates[key].AddUObject<TUObject>(inUserObj, InFunc);
}

	