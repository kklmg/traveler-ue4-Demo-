// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionData.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnVectorValueChanged, FVector);

namespace ActionData 
{
	const FName TeleportLocation = FName(TEXT("TeleportLocation"));
	const FName FlyToLocation = FName(TEXT("FlyToLocation"));
	const FName MovementAddition = FName(TEXT("MovementAddition"));
	const FName Projectile_SpawnLocation = FName(TEXT("Projectile_SpawnLocation"));
	const FName Projectile_Direction = FName(TEXT("Projectile_Direction"));
	const FName Projectile_Speed = FName(TEXT("Projectile_Speed"));
}


/**
 * 
 */
UCLASS()
class UActionData : public UObject
{
	GENERATED_BODY()
public:
	FOnVectorValueChanged OnReceiveMovementDelegate;

	FVector GetMovementInput();
	void SetMovementInput(FVector movementInput);

	UFUNCTION(BlueprintCallable)
	void WriteVectorData(FName key,FVector value);

	UFUNCTION(BlueprintCallable)
	bool TryReadVectorData(FName key,FVector& outValue);

	UFUNCTION(BlueprintCallable)
	void WriteFloatData(FName key, float value);

	UFUNCTION(BlueprintCallable)
	bool TryReadFloatData(FName key, float& outValue);

	UFUNCTION(BlueprintCallable)
	void WriteUObjectData(FName key, UObject* value);

	//UFUNCTION()
	bool TryReadUObjectData(FName key, UObject** outValue);

private:
	FVector _movementInput;
	TMap<FName, FVector> _mapVectorData;
	TMap<FName, float> _mapFloatData;
	TMap<FName, UObject*> _mapUObjectData;
};
