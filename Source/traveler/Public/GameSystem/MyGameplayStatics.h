// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Enums/EnumCombat.h"
#include "Damage/DamageData.h"
#include "MyGameplayStatics.generated.h"

class UCameraComponent;


/**
 * 
 */

enum EPlane
{
	Plane_None,
	Plane_XY,
	Plane_XZ,
	Plane_YZ,
};

UCLASS()
class TRAVELER_API UMyGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FVector InptAxisToCameraDirection(FVector inputAxis,UCameraComponent* cameraComp);	

	static float ComputeDistance(FVector from, FVector to, EPlane plane = Plane_None);

	static bool CauseDamage(AActor* damagedActor, FDamageData& damageData, FVector impactPoint, AActor* causer, APawn* instigator, bool bForce = false);
};
