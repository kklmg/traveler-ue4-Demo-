// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuiverComponent.h"
#include "Actors/ProjectileActorBase.h"

// Sets default values for this component's properties
UQuiverComponent::UQuiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_projectileLife = 30.f;
}


// Called when the game starts
void UQuiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuiverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


}

void UQuiverComponent::SpawnProjectiles(int count, APawn* instigator)
{
	for (int i = 0; i < count; ++i)
	{
		AProjectileActorBase* projectileIns = CreateOrGetInactivatedFromPool();
		if (projectileIns == nullptr) 
		{
			UE_LOG(LogTemp,Warning,TEXT("cant spawn projectile"))
			return;
		}
		projectileIns->SetInstigator(instigator);
		//projectileIns->VSetLife(30.f);
		//projectileIns->VSetDamage(Damage);
		projectileIns->VSetVelocity(FVector::ZeroVector);
		projectileIns->VSetIsActive(true);
	}
}

void UQuiverComponent::LaunchProjectiles(FVector Velocity)
{
	for (AProjectileActorBase* projectile : _projectilePool)
	{
		if (projectile)
		{
			projectile->VSetVelocity(Velocity);
		}
	}
}


AProjectileActorBase* UQuiverComponent::CreateOrGetInactivatedFromPool()
{
	//try get reusable actor 
	if (_inactivatedIndicies.Num() != 0)
	{
		int lastIndex = _inactivatedIndicies.Pop();

		if (lastIndex > _projectilePool.Num() - 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("Something Went wrong at pooling logic"));
			return nullptr;
		}
		return _projectilePool[lastIndex];
	}

	if (_ProjectileClass == nullptr)
	{
		return nullptr;
	}

	UWorld* world = GetWorld();
	if (world == nullptr)
	{
		return nullptr;
	}

	//make projectile instance
	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = GetOwner();
	AProjectileActorBase* projectileIns = world->SpawnActor<AProjectileActorBase>(_ProjectileClass, spawnParameters);

	if (projectileIns)
	{
		projectileIns->VSetPoolId(_projectilePool.Num());
		projectileIns->OnActorInactivated.BindUFunction(this, FName(TEXT("OnSpawnedActorInactivated")));
		_projectilePool.Add(projectileIns);
	}

	return projectileIns;
}

void UQuiverComponent::OnSpawnedActorInactivated(int poolId)
{
	_inactivatedIndicies.Add(poolId);
}
