// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UCapsuleComponent;
class UProjectileMovementComponent;
class ACreatureCharacter;

class AWeaponBase;

UCLASS()
class TRAVELER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Initialize(float damage, float intialSpeed = 3000.0f);

	void SetFlyingDirection(FVector direction);

	void Launch(float speed);

	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void VExecuteSpecialAction();

private:

	// Sphere collision component.
	//UPROPERTY(EditDefaultsOnly, Category = Projectile)
	//UCapsuleComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Projectile mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* ProjectileMeshComponent;

	// Projectile material
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic* ProjectileMaterialInstance;

	//Damage
	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float _damage;

	UPROPERTY()
	UDamageType* _damageType;
	
	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TSubclassOf<UDamageType> _damageTypeClass;

	// special action
	UPROPERTY(EditDefaultsOnly, Category = Action)
	FName _specialActionName;

	FVector _flyingDir;
};
