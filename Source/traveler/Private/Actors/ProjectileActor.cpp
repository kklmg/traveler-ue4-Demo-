// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ProjectileActor.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_basicScale = 1.0f; 
	_coneAngle = 5.0f;
	_shift = 0.0f;
	_damage = 1.0f;
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	_initialMeshScale = _meshComp->GetComponentScale();
	if(_meshComp)
	{
		//OnHit 
		_meshComp->OnComponentHit.AddDynamic(this, &AProjectileActor::VOnHit);
		_meshComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActor::VOnOverlapBegin);
	}
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_bIsActive == false) return;

	float speed = _projectileMovementComp->Velocity.Size();
	_shift += speed * DeltaTime;

	float scale = _shift * FMath::Tan(FMath::DegreesToRadians(_coneAngle));

	if (_scaleCurve)
	{
		float normalizedElapsedTime = FMath::Clamp(_elapsedLifeTime / _lifeTime, 0.0f, 1.0f);
		scale += _scaleCurve->GetFloatValue(normalizedElapsedTime) * _basicScale;
	}
	
	//SetActorScale3D(FVector(scale, scale, scale));
	_meshComp->SetWorldScale3D(FVector(scale, scale, scale)* _initialMeshScale);

	VApplyDamageToOverlapedActor();
}



void AProjectileActor::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity * 100.0f, Hit.ImpactPoint);
	}

	APawn* instigator = GetInstigator();

	if (OtherActor != instigator)
	{
		UGameplayStatics::ApplyDamage(OtherActor, _damage, instigator? GetInstigator()->GetController():nullptr, this, _damageTypeClass);
	}
	VInActivate();
}

void AProjectileActor::VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OverlappedComponent->IsSimulatingPhysics())
	{
		OverlappedComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity * 100.0f, SweepResult.ImpactPoint);
	}

	APawn* instigator = GetInstigator();

	if (OtherActor != instigator)
	{
		UGameplayStatics::ApplyDamage(OtherActor, _damage, instigator ? GetInstigator()->GetController() : nullptr, this, _damageTypeClass);
	}
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
	{
		VInActivate();
	}
}



void AProjectileActor::VApplyDamageToOverlapedActor()
{
	if(_meshComp)
	{
		TArray<AActor*> _actors;

		FDamageEvent damageEvent;

		_meshComp->GetOverlappingActors(_actors);
		
		for (AActor* actor : _actors)
		{
			actor->TakeDamage(_damage, damageEvent, nullptr, nullptr);
		}
	}
}

void AProjectileActor::VOnActive()
{
	Super::VOnActive();
}

void AProjectileActor::VOnInActive()
{
	Super::VOnInActive();

	_shift = 0.0f;
}


void AProjectileActor::VSetScaleCurve(UCurveFloat* curve)
{
	_scaleCurve = curve;
}

