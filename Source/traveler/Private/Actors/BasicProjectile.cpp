// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasicProjectile.h"
#include "GameSystem/MyGameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"


ABasicProjectile::ABasicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!_primitiveComp)
	{
		_staticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
		check(_staticMeshComp);

		_primitiveComp = _staticMeshComp;
		_primitiveComp->SetCollisionProfileName(FName("Projectile"));
		SetRootComponent(_primitiveComp);
	}

	_damageData.Damage = 100;
}

void ABasicProjectile::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	APawn* instigator = GetInstigator();

	_primitiveComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity * 0.1f, Hit.ImpactPoint);
	}

	if (OtherActor != instigator)
	{
		//apply damagge
		UMyGameplayStatics::CauseDamage(OtherActor, _damageData, Hit.ImpactPoint, this, GetInstigator());
	}
	
	Destroy();
}
