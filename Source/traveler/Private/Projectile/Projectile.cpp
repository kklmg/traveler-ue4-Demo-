// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Weapon/Weapon.h"
#include "Character/MyCharacter.h"
#include "Components/PawnCameraComponent.h"

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
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
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


void AProjectile::Launch(float speed)
{
	//get character
	AActor* instigator = GetInstigator();
	check(instigator != nullptr);

	AMyCharacter* character = Cast<AMyCharacter>(instigator);
	check(character != nullptr);

	//get weapon
	AActor* owner = GetOwner();
	check(owner != nullptr);

	AWeapon* weapon = Cast<AWeapon>(owner);
	check(character != nullptr);

	//get camera
	UPawnCameraComponent* cameraComponent = character->GetCameraComponent();
	check(cameraComponent != nullptr);

	//Get Camera Rotation Rotator
	FRotator cameraRotator = cameraComponent->GetComponentRotation();

	//get projectile location
	FVector projectileLocation = GetActorLocation();


	FHitResult hitResult;
	FVector cameraforwardVector = cameraComponent->GetForwardVector();
	FVector farPlaneCenter = cameraforwardVector * cameraComponent->OrthoFarClipPlane;
	FCollisionQueryParams CollisionParams;

	FVector hitLocation = farPlaneCenter;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, cameraComponent->GetComponentLocation(), farPlaneCenter, ECC_Visibility, CollisionParams))
	{
		if (hitResult.bBlockingHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("hitted something"));
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *hitResult.GetActor()->GetName()));
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Impact Point: %s"), *hitResult.ImpactPoint.ToString()));
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Normal Point: %s"), *hitResult.ImpactNormal.ToString()));
		}
		hitLocation = hitResult.ImpactPoint;
	}


	FVector projectileDirection = hitLocation - projectileLocation;
	projectileDirection.Normalize();
	//FRotator MuzzleRotation = projectileDirection.Rotation();
	

	//apply speed
	ProjectileMovementComponent->Velocity = projectileDirection * speed;


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
}

