// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/ObjectPoolBase.h"
#include "GameSystem/DebugMessageHelper.h"

UObjectPoolBase::UObjectPoolBase()
{
	_poolSize = 256;
}


UObject* UObjectPoolBase::SpawnUObject()
{
	check(_ObjectClassToSpawn);
	check(Cast<IPoolableInterface>(_ObjectClassToSpawn.GetDefaultObject()));

	//recycle
	if (_emptyIndicies.Num() > 0)
	{
		int32 emptySlotID = _emptyIndicies.Pop();
		check(_pool[emptySlotID])
		_pool[emptySlotID]->VActivate();
		
		return _pool[emptySlotID].GetObject();
	}

	//create new
	else if (_pool.Num() < _poolSize)
	{
		UObject* newObject = NewObject<UObject>(this, _ObjectClassToSpawn);
		check(newObject);
		IPoolableInterface* poolObjectInterface = Cast<IPoolableInterface>(newObject);
		check(poolObjectInterface);
		check(poolObjectInterface->VGetObjectInactiveDelegate());

		poolObjectInterface->VSetPoolId(_pool.Num());
		poolObjectInterface->VGetObjectInactiveDelegate()->BindUObject(this, &UObjectPoolBase::OnObjectInactive);
		poolObjectInterface->VActivate();

		_pool.Add(newObject);

		return newObject;
	}

	//todo (case: no empty slot in pool)
	else
	{	
		return nullptr;
	}
}

AActor* UObjectPoolBase::SpawnActor()
{
	check(_ObjectClassToSpawn);
	check(Cast<AActor>(_ObjectClassToSpawn.GetDefaultObject()))
	check(Cast<IPoolableInterface>(_ObjectClassToSpawn.GetDefaultObject()));

	if (GetWorld() == false) return nullptr;

	//recycle
	if (_emptyIndicies.Num() > 0)
	{
		int32 emptySlotID = _emptyIndicies.Pop();
		check(_pool[emptySlotID])
		_pool[emptySlotID]->VActivate();

		AActor* recycledActor = Cast<AActor>(_pool[emptySlotID].GetObject());

		return recycledActor;
	}

	//create new
	else if (_pool.Num() < _poolSize)
	{
		AActor* newActor = GetWorld()->SpawnActor(_ObjectClassToSpawn);
		check(newActor);
		IPoolableInterface* poolObjectInterface = Cast<IPoolableInterface>(newActor);
		check(poolObjectInterface);
		check(poolObjectInterface->VGetObjectInactiveDelegate());

		poolObjectInterface->VSetPoolId(_pool.Num());
		poolObjectInterface->VGetObjectInactiveDelegate()->BindUObject(this, &UObjectPoolBase::OnObjectInactive);
		poolObjectInterface->VActivate();
		_pool.Add(newActor);

		return newActor;
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
	if (poolableInterface)
	{
		_bIsActor = actor != nullptr;
		_ObjectClassToSpawn = objectClass;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("try to set non poolable object class"));
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
	if (!_ObjectClassToSpawn) return false;
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
