// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasicProjectile.h"
#include "GameSystem/MyGameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Data/TagNames.h"
#include "DrawDebugHelpers.h"


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

void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();

	UpdatePredictDecal();
}

void ABasicProjectile::EndPlay(EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);

}


void ABasicProjectile::VSetVelocity(FVector velocity)
{
	Super::VSetVelocity(velocity);
	UpdatePredictDecal();
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

	if (_hitEffectActorClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();

		FQuat quat = FQuat::FindBetweenVectors(FVector::UpVector, Hit.Normal);
		GetWorld()->SpawnActor<AActor>(_hitEffectActorClass, Hit.Location, quat.Rotator(), spawnParams);
	}

	if (OtherActor && _groundEffectActorClass && (OtherActor->ActorHasTag(NSTagName::Ground) || OtherActor->ActorHasTag(NSTagName::Wall)))
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = GetInstigator();

		FQuat quat = FQuat::FindBetweenVectors(FVector::UpVector, Hit.Normal);
		AActor* effectActor = GetWorld()->SpawnActor<AActor>(_groundEffectActorClass, Hit.Location, quat.Rotator(), spawnParams);
		effectActor->AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);
	}
	if(_predictDecalActorIns)
	{
		_predictDecalActorIns->Destroy();
	}

	Destroy();
}

void ABasicProjectile::UpdatePredictDecal()
{
	if (_predictDecalActorIns == nullptr && _predictDecalActorClass)
	{
		FActorSpawnParameters spawnParams;
		_predictDecalActorIns = GetWorld()->SpawnActor<AActor>(_predictDecalActorClass, spawnParams);
	}

	if (_predictDecalActorIns)
	{
		FVector dir = _projectileMovementComp->Velocity.GetSafeNormal();
			
		//get arrow hit location using line tracing
		FHitResult hitResult;
		FCollisionQueryParams CollisionParams;
		FVector LineTraceStart = GetActorLocation();
		FVector LineTraceEnd = LineTraceStart + dir * 20000.0f;

		//Execute line Tracing
		if (GetWorld()->LineTraceSingleByChannel(hitResult, LineTraceStart, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel3, CollisionParams))
		{
			FQuat quat = FQuat::FindBetweenVectors(FVector::UpVector, hitResult.Normal);
			quat = quat * FQuat(FVector::RightVector, FMath::DegreesToRadians(270));
			_predictDecalActorIns->SetActorLocationAndRotation(hitResult.ImpactPoint, quat);
		}
	}
}
