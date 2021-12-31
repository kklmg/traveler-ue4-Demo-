// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Data/EnumAttributeType.h"
#include "AttributeData.generated.h"



USTRUCT(BlueprintType)
struct FAttributeRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	EAttributeType AttributeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	FName LocaleKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = attributes)
	float GrowthRate;

	float GetGrowedValue(int level);
	FText GetLocaleText();
};




//
//UCLASS()
//class TRAVELER_API AAttributeData : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AAttributeData();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//};
