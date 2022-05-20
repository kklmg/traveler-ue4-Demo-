// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SphereProjectile.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameSystem/MyGameplayStatics.h"

// Sets default values
ASphereProjectile::ASphereProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!_primitiveComp)
	{
		_sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
		check(_sphereComp);

		_primitiveComp = _sphereComp;
		SetRootComponent(_primitiveComp);
		_primitiveComp->SetCollisionProfileName(FName("Particle"));
	}

	_coneAngle = 5.0f;
	_shift = 0.0f;
	_damage = 1.0f;
}

// Called when the game starts or when spawned
void ASphereProjectile::BeginPlay()
{
	Super::BeginPlay();

	_primaryScale = _primitiveComp->GetComponentScale();
	if(_primitiveComp)
	{
		//OnHit 
		_primitiveComp->OnComponentHit.AddDynamic(this, &ASphereProjectile::VOnHit);
		_primitiveComp->OnComponentBeginOverlap.AddDynamic(this, &ASphereProjectile::VOnOverlapBegin);
	}
}

// Called every frame
void ASphereProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_bIsActive == false) return;

	float speed = _projectileMovementComp->Velocity.Size();
	_shift += speed * DeltaTime;

	float scale = _shift * FMath::Tan(FMath::DegreesToRadians(_coneAngle))*2;

	if (_scaleCurve)
	{
		float normalizedElapsedTime = FMath::Clamp(_elapsedLifeTime / _lifeTime, 0.0f, 1.0f);
		scale += _scaleCurve->GetFloatValue(normalizedElapsedTime);
	}
	
	//SetActorScale3D(FVector(scale, scale, scale));
	//_primitiveComp->SetWorldScale3D(FVector(scale, scale, scale)* _initialMeshScale);

	SetActorScale3D(_primaryScale * scale);

	VApplyDamageToOverlapedActor();

	if (_elapsedLifeTime > _lifeTime)
	{
		VDeactivate();
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), _primaryScale.X * scale, 10.0f, FColor::Blue);
}



void ASphereProjectile::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	APawn* instigator = GetInstigator();

	if (OtherActor != instigator)
	{
		//apply damagge
		UMyGameplayStatics::CauseDamage(OtherActor, _damageData, Hit.ImpactPoint, this, GetInstigator());
	}
}

void ASphereProjectile::VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OverlappedComponent->IsSimulatingPhysics())
	{
		OverlappedComponent->AddImpulseAtLocation(_projectileMovementComp->Velocity * 100.0f, SweepResult.ImpactPoint);
	}

	APawn* instigator = GetInstigator();

	if (OtherActor != instigator)
	{
		//apply damagge
		UMyGameplayStatics::CauseDamage(OtherActor, _damageData, OtherActor->GetActorLocation(), this, GetInstigator());
	}
	if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
	{
		VDeactivate();
	}
}



void ASphereProjectile::VApplyDamageToOverlapedActor()
{
	if(_primitiveComp)
	{
		TArray<AActor*> _actors;

		FDamageEvent damageEvent;

		_primitiveComp->GetOverlappingActors(_actors);
		
		for (AActor* actor : _actors)
		{
			actor->TakeDamage(_damage, damageEvent, nullptr, nullptr);
		}
	}
}

bool ASphereProjectile::VActivate()
{
	return Super::VActivate();
}


bool ASphereProjectile::VDeactivate()
{
	if (Super::VDeactivate())
	{
		_shift = 0.0f;
		SetActorScale3D(_primaryScale);
		return true;
	}
	else
	{
		return false;
	}
}


void ASphereProjectile::VSetScaleCurve(UCurveFloat* curve)
{
	_scaleCurve = curve;
}

