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
	void WriteData_Bool(EActionDataKey key, bool value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Int32(EActionDataKey key, int32 value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Float(EActionDataKey key, float value);

	UFUNCTION(BlueprintCallable)
	void WriteData_FVector(EActionDataKey key, FVector value);

	UFUNCTION(BlueprintCallable)
	void WriteData_UObject(EActionDataKey key, UObject* value);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Bool(EActionDataKey key, bool& outValue,bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Int32(EActionDataKey key, int32& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Float(EActionDataKey key, float& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_FVector(EActionDataKey key, FVector& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	UObject* GetData_UObject(EActionDataKey key, bool bConsumeData = false);

	template<typename TUObject>
	TUObject* GetDataAs(EActionDataKey key);

	template<typename TUObject>
	FDelegateHandle Subscribe(EActionDataKey key, TUObject* inUserObj, void (TUObject::* InFunc)(UObject*));

	void DeleteData(EActionDataKey key);

protected:
	void NotifyData(EActionDataKey key);

	template<typename TUObject>
	TUObject* GetOrCreateDataAs(EActionDataKey key);

private:
	UPROPERTY()
	TMap<EActionDataKey, UObject*> _mapData;
	TMap<EActionDataKey, FMD_UObjectSignature> _mapDataDelegates;
};

template<typename TUObject>
TUObject* UActionBlackBoard::GetDataAs(EActionDataKey key)
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
TUObject* UActionBlackBoard::GetOrCreateDataAs(EActionDataKey key)
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
FDelegateHandle UActionBlackBoard::Subscribe(EActionDataKey key, TUObject* inUserObj, void (TUObject::* InFunc)(UObject*))
{
	if (_mapDataDelegates.Contains(key))
	{
		_mapDataDelegates.Add(key,FMD_UObjectSignature());
	}
	return 	_mapDataDelegates[key].AddUObject<TUObject>(inUserObj, InFunc);
}

	