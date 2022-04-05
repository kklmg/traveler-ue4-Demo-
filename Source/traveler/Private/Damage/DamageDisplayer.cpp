// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/DamageDisplayer.h"
#include "GameSystem/ObjectPoolBase.h"

UDamageDisplayer::UDamageDisplayer()
{
	_spawnInCircleRadius = 60.0f;
	_poolSize = 256;

	_damageDisplaySetting.Add(EDamageType::EDamage_Fire, FColor::Red);
	_damageDisplaySetting.Add(EDamageType::EDamage_Electricity, FColor::Yellow);
	_damageDisplaySetting.Add(EDamageType::EDamage_Ice, FColor::Cyan);
	_damageDisplaySetting.Add(EDamageType::EDamage_Physics, FColor::White);
	_damageDisplaySetting.Add(EDamageType::EDamage_Poison, FColor::Purple);
	_damageDisplaySetting.Add(EDamageType::EDamage_Water, FColor::Blue);
}



void UDamageDisplayer::Initialize()
{
	_widgetPool = NewObject<UObjectPoolBase>(this);
	_widgetPool->Initialize(_damageWidgetClass, _poolSize);
}

void UDamageDisplayer::ShowDamage(FDamageDisplayData damageDisplayData)
{
	if(!_damageWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No DamageWidgetClass!"));
		return;
	}
	if (!_widgetPool)
	{
		UE_LOG(LogTemp, Error, TEXT("No pool instance!"));
		return;
	}

	//Get random offset
	FVector2D offset = FMath::RandPointInCircle(_spawnInCircleRadius);

	//Get widget data
	FDamageWidgetData outDamageWidgetData;
	GetDamageWidgetData(damageDisplayData, offset, outDamageWidgetData);


	//Spawn widget 
	UDamageWidget* newDamageWidgetIns = _widgetPool->SpawnObject<UDamageWidget>();

	if(!newDamageWidgetIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("spawn Widget instance failed"));
		return;
	}

	newDamageWidgetIns->SetData(outDamageWidgetData);
}

void UDamageDisplayer::Tick(float DeltaTime)
{
	/*if (_widgetPool) 
	{
		_widgetPool->DrawDebugMessage();
	}*/
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
