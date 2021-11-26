// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CreatureCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/ActionComponent.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACreatureCharacter::ACreatureCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create action component
	_actionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
	check(_actionComponent != nullptr);

	//Create Attribute component
	_attributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	check(_attributeComponent != nullptr);

	//Enable the pawn to control camera rotation.
	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreatureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACreatureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACreatureCharacter::Ascend() 
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	AddMovementInput(FVector::UpVector);

	

	//FQuat pitch = FQuat(FVector::RightVector,FMath::DegreesToRadians(-1));
	//AddActorWorldRotation(pitch);
}

