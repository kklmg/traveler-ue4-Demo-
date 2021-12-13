// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

class UCharacterAttribute;
class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	UCharacterAttribute* GetAttribute(FName name);
private:
	void InitializeAttributes();

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
	TMap<FName,UCharacterAttribute*> _mapAttributes;

	UPROPERTY(EditDefaultsOnly,  Category = Attributes)
	UCharacterAttribute* _level;

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
	UDataTable* _attributeTable;
};
