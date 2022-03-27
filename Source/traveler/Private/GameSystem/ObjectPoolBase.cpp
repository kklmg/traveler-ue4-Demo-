// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/ObjectPoolBase.h"
#include "GameSystem/DebugMessageHelper.h"

UObjectPoolBase::UObjectPoolBase()
{
	_poolSize = 256;
}


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
		_pool[emptySlotID]->VActivate();

		return _pool[emptySlotID].GetObject();
	}

	//create new
	else if (_pool.Num() < _poolSize)
	{
		UObject* newObject;
		if (_bIsActor) 
		{
			UWorld* world = GetWorld();
			if(world)
			{
				newObject = GetWorld()->SpawnActor(_spawnObjectClass);
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			newObject = NewObject<UObject>(this, _spawnObjectClass);
		}
		
		IPoolableInterface* poolObjectInterface = Cast<IPoolableInterface>(newObject);

		if (newObject && poolObjectInterface)
		{
			_spawnedOrder.Add(_pool.Num());
			poolObjectInterface->VSetPoolId(_pool.Num());
			poolObjectInterface->VGetObjectInactiveDelegate().BindUFunction(this, FName("OnObjectInactive"));
			poolObjectInterface->VActivate();
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
	/*	int32 FirstID = _spawnedOrder[0];
		_pool[FirstID]->VInActivate();
		_pool[FirstID]->VActivate();
		_spawnedOrder.RemoveAt(0);
		
		return _pool[FirstID].GetObject();*/
		return nullptr;
	}

}

void UObjectPoolBase::Initialize(TSubclassOf<UObject> objectClass, int32 poolSize)
{
	_poolSize = poolSize;

	IPoolableInterface* poolableInterface = Cast<IPoolableInterface>(objectClass.GetDefaultObject());
	AActor* actor = Cast<AActor>(objectClass.GetDefaultObject());
	if(poolableInterface)
	{
		_bIsActor = actor != nullptr;
		_spawnObjectClass = objectClass;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("try to set non poolable object class"));
	}

	_emptyIndicies.Empty();
	_spawnedOrder.Empty();
	_pool.Empty();
}

void UObjectPoolBase::DrawDebugMessage()
{
	UDebugMessageHelper::Message_Int(TEXT("Empty Slot"), _emptyIndicies.Num());
	UDebugMessageHelper::Message_Int(TEXT("pool Size"), _pool.Num());
}

bool UObjectPoolBase::IsSpawnable()
{
	if (!_spawnObjectClass) return false;
	return _pool.Num() < _poolSize || _emptyIndicies.Num() > 0;
}

void UObjectPoolBase::OnObjectInactive(int32 index)
{
	_emptyIndicies.Add(index);

	//todo: find more efficent way
	_spawnedOrder.Remove(index);
	_spawnedOrder.Add(index);
}


