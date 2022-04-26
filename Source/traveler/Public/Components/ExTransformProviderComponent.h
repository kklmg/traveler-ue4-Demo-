// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/EnumTransformType.h"
#include "ExTransformProviderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UExTransformProviderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExTransformProviderComponent();

	void Initialize(USkeletalMeshComponent* skeletalMeshComp);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual bool TryGetSocketName(ETransform transfomType, FName& outSocketName);

	UFUNCTION(BlueprintCallable)
	bool TryGetTransform(ETransform transformType, ERelativeTransformSpace transformSpace, FTransform& outTransform);

private:
	UPROPERTY(EditDefaultsOnly, Category = Sockets)
	TMap<ETransform, FName> _boneNameMap;

	UPROPERTY(EditDefaultsOnly, Category = Sockets)
	TMap<ETransform, FTransform> _relativeTransfromMap;

	UPROPERTY()
	USkeletalMeshComponent* _skeletalMeshComp;
};