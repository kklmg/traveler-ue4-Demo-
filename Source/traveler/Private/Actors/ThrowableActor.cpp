// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ThrowableActor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AThrowableActor::AThrowableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!_rootSceneComp)
	{
		_rootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComp"));
		SetRootComponent(_rootSceneComp);
	}

	if(!_meshComp)
	{
		_meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
		_meshComp->AttachToComponent(_rootSceneComp,FAttachmentTransformRules::KeepRelativeTransform);
	}

	if (!_projectileMovementComp)
	{
		// Use this component to drive this projectile's movement.
		_projectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
		_projectileMovementComp->SetUpdatedComponent(_rootSceneComp);
		_projectileMovementComp->InitialSpeed = 0.0f;
		_projectileMovementComp->MaxSpeed = 3000.0f;
		_projectileMovementComp->bRotationFollowsVelocity = true;
		_projectileMovementComp->bShouldBounce = false;
		_projectileMovementComp->Bounciness = 0.3f;
		_projectileMovementComp->ProjectileGravityScale = 0.0f;
	}

	_basicScale = 1.0f; 
	_coneAngle = 5.0f;
	_shift = 0.0f;
	_damage = 1.0f;
}

// Called when the game starts or when spawned
void AThrowableActor::BeginPlay()
{
	Super::BeginPlay();

	_initialMeshScale = _meshComp->GetComponentScale();
	if(_meshComp)
	{
		//OnHit 
		_meshComp->OnComponentHit.AddDynamic(this, &AThrowableActor::VOnHit);
		//_meshComp->OnComponentBeginOverlap.AddDynamic(this, &AThrowableActor::VOnOverlapBegin);
	}

	//SetActorTransform(_spawnTransform);
}

// Called every frame
void AThrowableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isActive == false) return;

	_elapsedTime += DeltaTime;

	float speed = _projectileMovementComp->Velocity.Size();
	_shift += speed * DeltaTime;

	float scale = _shift * FMath::Tan(FMath::DegreesToRadians(_coneAngle));

	if (_scaleCurve)
	{
		float normalizedElapsedTime = FMath::Clamp(_elapsedTime / _life, 0.0f, 1.0f);
		scale += _scaleCurve->GetFloatValue(normalizedElapsedTime) * _basicScale;
	}
	
	//SetActorScale3D(FVector(scale, scale, scale));
	_meshComp->SetWorldScale3D(FVector(scale, scale, scale)* _initialMeshScale);

	VApplyDamageToOverlapedActor();

	if (_elapsedTime > _life)
	{
		VSetIsActive(false);
	}


}

void AThrowableActor::VSetLife(float life)
{
	_life = life;
}

void AThrowableActor::VSetDamage(float damage)
{
	_damage = damage;
}

void AThrowableActor::VOnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
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
	VSetIsActive(false);
}

void AThrowableActor::VOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
	VSetIsActive(false);
}


bool AThrowableActor::VIsActive()
{
	return _isActive;
}

void AThrowableActor::VSetIsActive(bool isActive)
{
	if (_isActive == isActive) return;

	_isActive = isActive;

	SetActorTickEnabled(_isActive);
	SetActorHiddenInGame(!_isActive);

	if (!_isActive)
	{
		_elapsedTime = 0.0f;
		_shift = 0.0f;
		OnActorInactivated.ExecuteIfBound(_poolId);
	}
}

int AThrowableActor::VGetPoolId()
{
	return _poolId;
}

void AThrowableActor::VSetPoolId(int poolId)
{
	_poolId = poolId;
}

void AThrowableActor::VApplyDamageToOverlapedActor()
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

void AThrowableActor::VSetScale(float scale)
{
	_basicScale = scale;
	//SetActorScale3D(FVector(scale,scale,scale));
}



void AThrowableActor::VSetVelocity(FVector velocity)
{
	_projectileMovementComp->Velocity = velocity;
}

void AThrowableActor::VSetScaleCurve(UCurveFloat* curve)
{
	_scaleCurve = curve;
}

