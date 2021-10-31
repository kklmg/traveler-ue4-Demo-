// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command/CommandBase.h"
#include "CommandCamera.generated.h"

class UCameraComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UCommandCamera : public UCommandBase
{
	GENERATED_BODY()

public:
	void Initialize(UCameraComponent* cameraComponent);
private:
	UCameraComponent* _cameraComponent;
};
