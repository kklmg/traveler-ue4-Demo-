// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/DamageDisplayer.h"

UDamageDisplayer::UDamageDisplayer()
{
	_spawnInCircleRadius = 60.0f;
	_poolSize = 200;
}


void UDamageDisplayer::ShowDamage(FDamageDisplayData damageDisplayData)
{
	if(!_damageWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No DamageWidgetClass!"));
		return;
	}

	if (_widgetPool.Num() < _poolSize && _emptySlots.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No empty pool slot!"));
		return;
	}

	//make widget Instance
	UDamageWidget* newDamageWidgetIns = NewObject<UDamageWidget>(this, _damageWidgetClass);

	if(!newDamageWidgetIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("make Widget instance failed"));
		return;
	}

	//Get random offset
	FVector2D randomOffset = FMath::RandPointInCircle(_spawnInCircleRadius);

	//set widget data
	if (_damageDisplaySetting.Contains(damageDisplayData.DamageType))
	{
		newDamageWidgetIns->SetData(damageDisplayData.Location, damageDisplayData.Damage, _damageDisplaySetting[damageDisplayData.DamageType], randomOffset);
	}
	else
	{
		newDamageWidgetIns->SetData(damageDisplayData.Location, damageDisplayData.Damage, FDamageWidgetData(), randomOffset);
	}


	//add new widget to widgetPool
	if (_emptySlots.Num() > 0)
	{
		int32 index = _emptySlots.Pop();
		_widgetPool[index] = newDamageWidgetIns;
	}

	else /*if (_widgetPool.Num() < _poolSize)*/
	{
		_widgetPool.Add(newDamageWidgetIns);
	}

	//add to viewPort
	newDamageWidgetIns->AddToViewport(100);
}

void UDamageDisplayer::Tick(float DeltaTime)
{
	for (int32 i = 0; i < _widgetPool.Num(); ++i)
	{
		if (_widgetPool[i] && _widgetPool[i]->IsLifeOver())
		{
			_widgetPool[i]->RemoveFromViewport();
			_widgetPool[i]->RemoveFromParent();
			_widgetPool[i] = nullptr;
		}
	}
}