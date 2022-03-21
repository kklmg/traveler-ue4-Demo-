// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/EnumAttributeType.h"
#include "AttributeComponent.generated.h"

class UCharacterAttribute;
class UDataTable;
class UCostData;
class UAnimationModelBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();
protected:

	virtual void InitializeComponent() override;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	UCharacterAttribute* GetAttribute(EAttributeType attributeType);

	UFUNCTION(BlueprintCallable)
	bool SetAttribute(EAttributeType attributeType, float newValue);

	UFUNCTION(BlueprintCallable)
	bool SetAttributeChange(EAttributeType attributeType, float deltaValue);

	UFUNCTION(BlueprintCallable)
	bool CanConsumeStatus(EAttributeType attributeType, float costValue);

	UFUNCTION(BlueprintCallable)
	bool CanConsume(UCostData* costData);



	UFUNCTION(BlueprintCallable)
	bool TryConsume(UCostData * costData);


private:
	void InitializeAttributes();

	UPROPERTY()
	UAnimationModelBase* _animationViewModel;

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
	TMap<EAttributeType,UCharacterAttribute*> _mapAttributes;

	UPROPERTY(EditDefaultsOnly,  Category = Attributes)
	UCharacterAttribute* _level;

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
	UDataTable* _attributeTable;
};
