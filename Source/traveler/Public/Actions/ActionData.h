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

private:
	FVector _movementInput;
	TMap<FName, FVector> _mapVectorData;
};
