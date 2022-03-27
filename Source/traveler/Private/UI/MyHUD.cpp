// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyHUD.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (_damageDisplayerClass)
	{
		_damageDisplayerIns = NewObject<UDamageDisplayer>(this, _damageDisplayerClass);
		if(!_damageDisplayerIns)
		{
			UE_LOG(LogTemp, Warning, TEXT("make instance of DamageDisplayer failed"));
		}
		_damageDisplayerIns->Initialize();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No assigned DamageType Class"));
	}
}

void AMyHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(_damageDisplayerIns)
	{
		_damageDisplayerIns->Tick(DeltaTime);
	}
}

void AMyHUD::ShowDamage(FDamageDisplayData damageDisplayData)
{
	if (_damageDisplayerIns)
	{
		_damageDisplayerIns->ShowDamage(damageDisplayData);
	}
}
