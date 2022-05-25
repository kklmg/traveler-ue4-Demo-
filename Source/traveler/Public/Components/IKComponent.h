// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/EnumTransformType.h"
#include "Data/IKData.h"
#include "IKComponent.generated.h"

class IExtraTransformProvider;

class UAnimationModelBase;

class ACharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UIKComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIKComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FIKData FootTrace(ETransformType meshSocketType);
	
private:
	UPROPERTY(EditAnywhere)
	bool _bActivateFootIK;

	UPROPERTY(EditDefaultsOnly)
	float _traceOffset;

	UPROPERTY(EditAnywhere)
	ACharacter* _character;

	UPROPERTY()
	class UAnimationModelBase* _animationViewModel;

	UPROPERTY()
	class UExTransformProviderComponent* _exTransformProviderComp;

	UPROPERTY()
	UIKFootData* _footIKData;

	float _halfHeight;
};
