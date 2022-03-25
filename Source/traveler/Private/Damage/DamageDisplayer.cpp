// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/DamageDisplayer.h"

UDamageDisplayer::UDamageDisplayer()
{
	_spawnInCircleRadius = 60.0f;
	_poolSize = 200;

	_damageDisplaySetting.Add(EDamageType::EDamage_Fire, FColor::Red);
	_damageDisplaySetting.Add(EDamageType::EDamage_Electricity, FColor::Yellow);
	_damageDisplaySetting.Add(EDamageType::EDamage_Ice, FColor::Cyan);
	_damageDisplaySetting.Add(EDamageType::EDamage_Physics, FColor::White);
	_damageDisplaySetting.Add(EDamageType::EDamage_Poison, FColor::Purple);
	_damageDisplaySetting.Add(EDamageType::EDamage_Water, FColor::Blue);
}



void UDamageDisplayer::ShowDamage(FDamageDisplayData damageDisplayData)
{
	if(!_damageWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No DamageWidgetClass!"));
		return;
	}

	if (_widgetPool.Num() >= _poolSize && _emptySlots.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No empty pool slot!"));
		return;
	}

	//Get random offset
	FVector2D offset = FMath::RandPointInCircle(_spawnInCircleRadius);

	//Get widget data
	FDamageWidgetData outDamageWidgetData;
	GetDamageWidgetData(damageDisplayData, offset, outDamageWidgetData);


	//make widget Instance
	UDamageWidget* newDamageWidgetIns = NewObject<UDamageWidget>(this, _damageWidgetClass);

	if(!newDamageWidgetIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("make Widget instance failed"));
		return;
	}

	newDamageWidgetIns->SetData(outDamageWidgetData);

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

void UDamageDisplayer::GetDamageWidgetData(FDamageDisplayData damageDisplayData, FVector2D offset, FDamageWidgetData& outDamageWidgetData)
{
	if (_damageDisplaySetting.Contains(damageDisplayData.DamageType))
	{
		outDamageWidgetData = _damageDisplaySetting[damageDisplayData.DamageType];
	}

	outDamageWidgetData.Damage = damageDisplayData.Damage;
	outDamageWidgetData.TextLocation = damageDisplayData.Location;
	outDamageWidgetData.TextOffset = offset;

	if (_textScaleCurve)
	{
		outDamageWidgetData.TextScale = _textScaleCurve->GetFloatValue(damageDisplayData.Damage);
	}
}
