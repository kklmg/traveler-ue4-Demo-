// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/ViewModel.h"
#include "ViewModelBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UViewModelBase : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UReactiveDataBase* GetData(FName dataKey);

	UFUNCTION(BlueprintCallable)
	UReactive_Int* GetData_Int(FName dataKey);
	UFUNCTION(BlueprintCallable)
	UReactive_Float* GetData_Float(FName dataKey);
	UFUNCTION(BlueprintCallable)
	UReactive_Bool* GetData_Bool(FName dataKey);
	UFUNCTION(BlueprintCallable)
	UReactive_UInt8* GetData_UInt8(FName dataKey);
	UFUNCTION(BlueprintCallable)
	UReactive_Vector* GetData_Vector(FName dataKey);
	UFUNCTION(BlueprintCallable)
	UReactive_Quat* GetData_Quat(FName dataKey);
	UFUNCTION(BlueprintCallable)
	UReactive_UObject* GetData_UObject(FName dataKey);

	void SetInt(FName dataKey, int value);
	void SetFloat(FName dataKey, float value);
	void SetBool(FName dataKey, bool value);
	void SetVector(FName dataKey, FVector value);
	void SetQuat(FName dataKey, FQuat value);
	void SetUInt8(FName dataKey, uint8 value);
	void SetUObject(FName dataKey, UObject* value);

	void ClearData();

private:
	template<typename TData>
	TData* GetOrCreate(FName dataKey);

private:
	UPROPERTY()
	TMap<FName, UReactiveDataBase*> _dataMap;
};


template<typename TData>
TData* UViewModelBase::GetOrCreate(FName dataKey)
{
	TData* data;
	if (_dataMap.Contains(dataKey))
	{
		data = Cast<TData>(_dataMap[dataKey]);
	}
	else
	{
		data = NewObject<TData>(this);
		_dataMap.Add(dataKey, data);
	}
	return data;
}