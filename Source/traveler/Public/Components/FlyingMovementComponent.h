// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlyingMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UFlyingMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFlyingMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	void AddLocalPitch(float scale);
	void AddLocalRoll(float scale);
	void AddWorldYaw(float scale);

	void ClearPitchRoll();




	//virtual void VExecute() override;
	//virtual void VTick(float deltaTime) override;

private:
	float _localPitchInput;
	float _localRollInput;
	float _worldYawInput;
	bool _bHasInput;


	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _flyingSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Turning)
	float _pitchRate;
	UPROPERTY(EditDefaultsOnly, Category = Turning)
	float _yawRate;
	UPROPERTY(EditDefaultsOnly, Category = Turning)
	float _rollRate;

	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _pitchAngleLimit;
	UPROPERTY(EditDefaultsOnly, Category = speed)
	float _RollAngleLimit;
};
