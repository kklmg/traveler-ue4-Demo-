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
	UObject* SpawnObject();

	void SetSpawnObjectClass(TSubclassOf<UObject> objectClass);

protected:

	UFUNCTION()
	void OnObjectDie(int32 index);

private:
	TSubclassOf<UObject> _spawnObjectClass;
	TArray<TScriptInterface<IPoolableInterface>> _pool;
	TArray<int32> _emptyIndicies;
	TArray<int32> _spawnedOrder;

	int32 _poolSize;	
};
