// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interface/PoolableInterface.h"
#include "ObjectPoolBase.generated.h"

/**
 * 
 */
UCLASS()
class TRAVELER_API UObjectPoolBase : public UObject
{
	GENERATED_BODY()
public:
	UObjectPoolBase();

	UObject* SpawnObject();

	template<typename T>
	T* SpawnObject();

	void Initialize(TSubclassOf<UObject> objectClass, int32 poolSize);
	bool IsSpawnable();

	void DrawDebugMessage();
protected:

	UFUNCTION()
	void OnObjectInactive(int32 index);

	
private:
	UPROPERTY()
	TSubclassOf<UObject> _spawnObjectClass;

	UPROPERTY()
	TArray<TScriptInterface<IPoolableInterface>> _pool;

	TArray<int32> _emptyIndicies;
	TArray<int32> _spawnedOrder; //todo: find more efficent way
	
	int32 _poolSize;
	bool _bIsActor;
};


template<typename T>
T* UObjectPoolBase::SpawnObject()
{
	return Cast<T>(SpawnObject());
}