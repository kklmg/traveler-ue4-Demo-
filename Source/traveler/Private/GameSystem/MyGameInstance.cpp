// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "GameInstance::Init");
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
	Super::BeginDestroy();
}
