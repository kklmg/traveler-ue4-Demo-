// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/PawnCameraComponent.h"
#include "Weapon/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/CreatureCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//if (!RootComponent)
	//{
	//	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	//}
	//if (!CollisionComponent)
	//{
	//	// Use a sphere as a simple collision representation.
	//	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	//	// Set the sphere's collision radius.
	//	CollisionComponent->InitCapsuleSize(10, 10);
	//	// Set the root component to be the collision component.
	//	RootComponent = CollisionComponent;

	//	// Set the sphere's collision profile name to "Projectile".
	//	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	//	// Event called when component hits something.
	//	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	//}
	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		RootComponent = ProjectileMeshComponent;


		ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
		//ProjectileMeshComponent->SetupAttachment(RootComponent);

			//	// Set the sphere's collision profile name to "Projectile".
	//	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	//	// Event called when component hits something.
	//	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
		ProjectileMovementComponent->InitialSpeed = 0.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	_damage = 10;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (GetInstigator())
	{
		ProjectileMeshComponent->IgnoreActorWhenMoving(GetInstigator(), true);
	}
	if (_damageTypeClass) 
	{
		_damageType = NewObject<UDamageType>(this, _damageTypeClass);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Initialize(float damage,float intialSpeed)
{
	_damage = damage;
	ProjectileMovementComponent->InitialSpeed = intialSpeed;
}

// Function that initializes the projectile's velocity in the shoot direction.
void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::SetFlyingDirection(FVector direction)
{
	direction.Normalize();
	_flyingDir = direction;
}


void AProjectile::Launch(float speed)
{
	//apply speed
	ProjectileMovementComponent->Velocity = _flyingDir * speed;


	//Bind Special Action
	ACreatureCharacter* character = GetInstigator<ACreatureCharacter>();
	if (character) 
	{
		//character->Action3ButtonDownDelegate.BindUFunction(this, FName("VExecuteSpecialAction"));
	}
	//DrawDebugLine(GetWorld(), MuzzleLocation, hitLocation, FColor::Blue, false, 2.0f);
}


// Function that is called when the projectile hits something.
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("hitted by projectile"));
	}
	AttachToComponent(OtherComponent, FAttachmentTransformRules::KeepWorldTransform);

	FTimerHandle WaitHandle;
	float WaitTime = 5;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	{
		Destroy();

	}), WaitTime, false);

	if (OtherActor != GetInstigator())
	{
		UGameplayStatics::ApplyDamage(OtherActor, _damage, GetInstigator()->GetController(), this, _damageTypeClass);
	}
}

void AProjectile::VExecuteSpecialAction()
{
	UE_LOG(LogTemp, Warning, TEXT("called not implemented function: ExecuteSpecialAction"));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("projectile action"));
}

