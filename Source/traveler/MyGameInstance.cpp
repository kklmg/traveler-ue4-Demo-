// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "GameInstance::Init");
}

void UMyGameInstance::StartGameInstance()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "GameInstance::StartGameInstance");
}

void UMyGameInstance::OnStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "GameInstance::OnStart"); 
}
