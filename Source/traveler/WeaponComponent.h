// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponChanged, AWeapon*,weapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetWeapon(AWeapon* weapon);

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FWeaponChanged onWeaponChanged;

	UPROPERTY(EditDefaultsOnly, Category = "DefaultWeapon")
	TSubclassOf<AWeapon> DefaultWeapon;
private:
	AWeapon* _aWeapon;
};
