// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "GameInstance::Init");

	_gameManager = new GameManager();
}

void UMyGameInstance::StartGameInstance()
{
	Super::StartGameInstance();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "GameInstance::StartGameInstance");


}

void UMyGameInstance::OnStart()
{
	Super::OnStart();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "GameInstance::OnStart"); 
}

void UMyGameInstance::BeginDestroy()
{
	if (_gameManager != nullptr) 
	{
		delete(_gameManager);
		_gameManager = nullptr;
	}
	Super::BeginDestroy();
}
