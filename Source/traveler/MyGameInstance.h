// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.h"
#include "MyGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class TRAVELER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	GameManager* _gameManager;

private:
	void Init() override;
	void StartGameInstance() override;
	void OnStart() override;
};
