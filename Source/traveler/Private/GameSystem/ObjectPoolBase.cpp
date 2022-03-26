// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/ObjectPoolBase.h"

UObject* UObjectPoolBase::SpawnObject()
{
	if (!_spawnObjectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No SpawnObjectClass!"));
		return nullptr;
	}

	//recycle
	if (_emptyIndicies.Num() > 0)
	{
		int32 emptySlotID = _emptyIndicies.Pop();
		_spawnedOrder.Add(emptySlotID);

		return _pool[emptySlotID].GetObject();
	}

	//create new
	else if (_pool.Num() < _poolSize)
	{
		UObject* newObject = NewObject<UObject>(this, _spawnObjectClass);
		IPoolableInterface* poolObjectInterface = Cast<IPoolableInterface>(newObject);

		if (newObject && poolObjectInterface)
		{
			_spawnedOrder.Add(_pool.Num());
			poolObjectInterface->VSetPoolId(_pool.Num());
			poolObjectInterface->VGetPoolObjectDieDelegate().BindUFunction(this, FName("OnObjectDie"));
			poolObjectInterface->VSetIsActive(true);
			_pool.Add(newObject);

			return newObject;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create uobject instance!"))
				return nullptr;
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No free slot in pool!"));
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

void UObjectPoolBase::OnObjectDie(int32 index)
{
	_emptyIndicies.Add(index);
	_spawnedOrder.Remove(index);
	_spawnedOrder.Add(index);
}


