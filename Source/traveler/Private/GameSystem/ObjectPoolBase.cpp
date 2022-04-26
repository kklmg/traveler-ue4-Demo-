// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/ObjectPoolBase.h"
#include "GameSystem/DebugMessageHelper.h"

UObjectPoolBase::UObjectPoolBase()
{
	_poolSize = 256;
}


UObject* UObjectPoolBase::SpawnObject()
{
	check(_spawnObjectClass);

	//recycle
	if (_emptyIndicies.Num() > 0)
	{
		int32 emptySlotID = _emptyIndicies.Pop();
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
			poolObjectInterface->VSetPoolId(_pool.Num());

			check(poolObjectInterface->VGetObjectInactiveDelegate());
			poolObjectInterface->VGetObjectInactiveDelegate()->BindUObject(this, &UObjectPoolBase::OnObjectInactive);
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
	{	//todo
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

void UObjectPoolBase::EmptyPool()
{
	for (auto element : _pool)
	{
		element->VMarkDestroy();
	}
	_pool.Empty();
}

void UObjectPoolBase::OnObjectInactive(int32 index)
{
	_emptyIndicies.Add(index);
}


