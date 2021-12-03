// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

class UCameraComponent;

/**
 * 
 */
UCLASS()
class TRAVELER_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FVector InptAxisToCameraDirection(FVector inputAxis,UCameraComponent* cameraComp);	
};
