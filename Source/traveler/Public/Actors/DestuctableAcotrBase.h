// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestuctableAcotrBase.generated.h"

class ULifeControlComponent;
class UAttributeComponent;
class UActorUIComponent;
class UStatusComponent;
class UExTransformProviderComponent;
class UDamageHandlerComponent;
class UEffectControllerComponent;
class UEventBrokerComponent;


UCLASS()
class TRAVELER_API ADestuctableAcotrBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestuctableAcotrBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UEventBrokerComponent* _eventBrokerComponent;

	UPROPERTY(VisibleAnywhere)
	ULifeControlComponent* _lifeControlComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* _meshComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStatusComponent* _statusComponent;

	UPROPERTY(VisibleAnywhere)
	UActorUIComponent* _actorUIComponent;

	UPROPERTY(VisibleAnywhere)
	UExTransformProviderComponent* _ExTransformProviderComp;

	UPROPERTY(VisibleAnywhere)
	UDamageHandlerComponent* _damageHandlerComponent;

	UPROPERTY(VisibleAnywhere)
	UEffectControllerComponent* _effectControllerComponent;
};
