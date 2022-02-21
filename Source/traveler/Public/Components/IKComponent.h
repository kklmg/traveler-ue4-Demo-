// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/EnumMeshSocketType.h"
#include "Data/IKData.h"
#include "IKComponent.generated.h"

class IAnimationModelProvider;
class IMeshSocketTransformProvider;


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

	FIKData FootTrace(EMeshSocketType meshSocketType);

	UFUNCTION(BlueprintCallable)
	FIKData GetIKData_LeftFoot();

	UFUNCTION(BlueprintCallable)
	FIKData GetIKData_RightFoot();
	
private:
	UPROPERTY(EditAnywhere)
	bool _bActivateFootIK;

	IAnimationModelProvider* _animationModelProvider;
	IMeshSocketTransformProvider* _meshSocketProvider;

	FIKData _IKDataLeftFoot;
	FIKData _IKDataRightFoot;
};
