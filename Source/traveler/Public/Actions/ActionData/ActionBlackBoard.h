// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnumActionType.h"
#include "ActionBlackBoard.generated.h"

class UActionDataBase;


template<typename T>
class TActionDataBlackBoard
{
public:
	bool TryGetData(EActionData key, T& outValue)
	{
		if (_mapActionData.Contains(key))
		{
			outValue = _mapActionData[key];
			return true;
		}
		return false;
	}
	void WriteData(EActionData key, T value)
	{
		if(_mapActionData.Contains(key))
		{
			if(_mapActionData[key] == value)
			{
				return;
			}
			else
			{
				_mapActionData[key] = value;
				BroardCast(key);
			}
		}
		else
		{
			_mapActionData.Add(key, value);
			BroardCast(key);
		}
	}
	void DeleteData(EActionData key)
	{
		_mapActionData.Remove(key);
	}

	TMulticastDelegate<void(T)>& GetDelegate(EActionData key)
	{
		if(_mapActionDataChangedDelegates.Contains(key))
		{
			return _mapActionDataChangedDelegates[key];
		}
		else
		{
			_mapActionDataChangedDelegates.Add(key, TMulticastDelegate<void(T)>());
			return _mapActionDataChangedDelegates[key];
		}
	}
	void BroardCast(EActionData key)
	{
		if (_mapActionDataChangedDelegates.Contains(key) && _mapActionData.Contains(key))
		{
			_mapActionDataChangedDelegates[key].Broadcast(_mapActionData[key]);
		}
	}


private:
	TMap<EActionData, T> _mapActionData;
	TMap<EActionData, TMulticastDelegate<void(T)>> _mapActionDataChangedDelegates;
};


/**
 * 
 */
UCLASS(Blueprintable)
class TRAVELER_API UActionBlackBoard : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void WriteData_Bool(EActionData key, bool value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Int(EActionData key, int value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Float(EActionData key, float value);

	UFUNCTION(BlueprintCallable)
	void WriteData_FVector(EActionData key, FVector value);

	UFUNCTION(BlueprintCallable)
	void WriteData_UObject(EActionData key, UObject* value);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Bool(EActionData key, bool& outValue,bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Int(EActionData key, int& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Float(EActionData key, float& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_FVector(EActionData key, FVector& outValue, bool bConsumeData = false);

	//UFUNCTION()
	bool TryGetData_UObject(EActionData key, UObject** outValue, bool bConsumeData = false);

	void DeleteData(EActionData key);

private:
	TActionDataBlackBoard<bool> _boolData;
	TActionDataBlackBoard<int> _intData;
	TActionDataBlackBoard<float> _floatData;
	TActionDataBlackBoard<FVector> _vectorData;
	TActionDataBlackBoard<FQuat> _quatData;
	TActionDataBlackBoard<UObject*> _objectData;
};
