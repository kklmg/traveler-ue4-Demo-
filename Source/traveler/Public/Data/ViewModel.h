// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewModel.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_bool, bool, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Int, int, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Float, float, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Vector, FVector, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_Quat, FQuat, value);


UCLASS(BlueprintType)
class TRAVELER_API UReactiveDataBase : public UObject
{
	GENERATED_BODY()
public:
};



UCLASS(BlueprintType)
class TRAVELER_API UReactive_Bool : public UReactiveDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDelegate_bool OnValueChanged;
public:
	void SetValue(bool value);
private:
	UPROPERTY()
	bool _value;
};

UCLASS(BlueprintType)
class TRAVELER_API UReactive_Int : public UReactiveDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDelegate_Int OnValueChanged;
public:
	void SetValue(int value);
private:
	UPROPERTY()
	int _value;
};


UCLASS(BlueprintType)
class TRAVELER_API UReactive_Float : public UReactiveDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDelegate_Float OnValueChanged;
public:
	void SetValue(float value);
private:
	UPROPERTY()
	float _value;
};

UCLASS(BlueprintType)
class TRAVELER_API UReactive_Vector : public UReactiveDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDelegate_Vector OnValueChanged;
public:
	void SetValue(FVector value);
private:
	UPROPERTY()
	FVector _value;
};

UCLASS(BlueprintType)
class TRAVELER_API UReactive_Quat : public UReactiveDataBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDelegate_Quat OnValueChanged;
public:
	void SetValue(FQuat value);
private:
	UPROPERTY()
	FQuat _value;
};

