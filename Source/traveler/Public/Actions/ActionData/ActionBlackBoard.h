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
	bool TryGetData(EActionDataKey key, T& outValue)
	{
		if (_mapActionData.Contains(key))
		{
			outValue = _mapActionData[key];
			return true;
		}
		return false;
	}
	void WriteData(EActionDataKey key, T value)
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
	void DeleteData(EActionDataKey key)
	{
		_mapActionData.Remove(key);
	}

	TMulticastDelegate<void(T)>& GetDelegate(EActionDataKey key)
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
	void BroardCast(EActionDataKey key)
	{
		if (_mapActionDataChangedDelegates.Contains(key) && _mapActionData.Contains(key))
		{
			_mapActionDataChangedDelegates[key].Broadcast(_mapActionData[key]);
		}
	}


private:
	UPROPERTY()
	TMap<EActionDataKey, T> _mapActionData;
	TMap<EActionDataKey, TMulticastDelegate<void(T)>> _mapActionDataChangedDelegates;
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
	void WriteData_Bool(EActionDataKey key, bool value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Int(EActionDataKey key, int value);

	UFUNCTION(BlueprintCallable)
	void WriteData_Float(EActionDataKey key, float value);

	UFUNCTION(BlueprintCallable)
	void WriteData_FVector(EActionDataKey key, FVector value);

	//UFUNCTION(BlueprintCallable)
	//void WriteData_UObject(EActionDataKey key, UObject* value);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Bool(EActionDataKey key, bool& outValue,bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Int(EActionDataKey key, int& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_Float(EActionDataKey key, float& outValue, bool bConsumeData = false);

	UFUNCTION(BlueprintCallable)
	bool TryGetData_FVector(EActionDataKey key, FVector& outValue, bool bConsumeData = false);

	//UFUNCTION()
	//bool TryGetData_UObject(EActionDataKey key, UObject** outValue, bool bConsumeData = false);

	TMulticastDelegate<void(bool)>& GetValueChangedDelegate_Bool(EActionDataKey key);
	TMulticastDelegate<void(int)>& GetValueChangedDelegate_Int(EActionDataKey key);
	TMulticastDelegate<void(float)>& GetValueChangedDelegate_Float(EActionDataKey key);
	TMulticastDelegate<void(FVector)>& GetValueChangedDelegate_FVector(EActionDataKey key);
	TMulticastDelegate<void(FQuat)>& GetValueChangedDelegate_Fquat(EActionDataKey key);


	void DeleteData(EActionDataKey key);

private:
	TActionDataBlackBoard<bool> _boolData;
	TActionDataBlackBoard<int> _intData;
	TActionDataBlackBoard<float> _floatData;
	TActionDataBlackBoard<FVector> _vectorData;
	TActionDataBlackBoard<FQuat> _quatData;

	//TActionDataBlackBoard<UObject*> _objectData;
};
