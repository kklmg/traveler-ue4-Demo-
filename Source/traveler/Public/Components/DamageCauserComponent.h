// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damage/DamageData.h"
#include "DamageCauserComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UDamageCauserComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageCauserComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void CauseDamageTo(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void CauseContinousDamageTo(AActor* actor);

	UFUNCTION(BlueprintCallable)
	void StopContinousDamage(AActor* actor);
private:
	UPROPERTY(EditDefaultsOnly)
	float _applyDamageRate;

	UPROPERTY(EditDefaultsOnly)
	FDamageData _damageData;

	UPROPERTY()
	TMap<AActor*,FTimerHandle> _damageTimerHandlers;
};
