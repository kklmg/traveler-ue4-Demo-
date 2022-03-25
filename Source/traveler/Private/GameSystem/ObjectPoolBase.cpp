// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/ObjectPoolBase.h"

UObject* UObjectPoolBase::SpawnObject()
{
	if (_spawnObjectClass)
	{
		UObject* newObject = NewObject<UObject>(this, _spawnObjectClass);
		_pool.Add(newObject);
		return newObject;
	}
	else
	{
		return nullptr;
	}

}

void UObjectPoolBase::SetSpawnObjectClass(TSubclassOf<UObject> objectClass)
{
	IPoolableInterface* poolableInterface = Cast<IPoolableInterface>(objectClass.GetDefaultObject());
	if(poolableInterface)
	{
		_spawnObjectClass = objectClass;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("try to set non poolable object class"));
	}
}

UObject* UObjectPoolBase::GetOrCreate()
{
	if (!_spawnObjectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No SpawnObjectClass!"));
		return nullptr;
	}

	if (_pool.Num() >= _poolSize && _emptyIndicies.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No empty slot in pool!"));
		return nullptr;
	}

	UObject* newObject = NewObject<UObject>(this, _spawnObjectClass);
	_pool.Add(newObject);
	return newObject;
}
