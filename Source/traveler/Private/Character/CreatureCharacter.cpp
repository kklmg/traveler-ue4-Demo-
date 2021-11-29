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

UAttributeComponent* ACreatureCharacter::GetAttributeComponent()
{
	return _attributeComponent;
}

UActionComponent* ACreatureCharacter::GetActionComponent()
{
	return _actionComponent;
}

void ACreatureCharacter::ExecuteAction(FName actionName)
{
	if (_actionComponent) 
	{
		_actionComponent->ExecuteAction(actionName);
	}
}

UActionData* ACreatureCharacter::GetActionData()
{
	return _actionComponent->GetActionData();
}

FName ACreatureCharacter::GetMeshSocketNameByType(EMeshSocketType meshSocketType)
{
	if (_socketsMap.Contains(meshSocketType))
	{
		return _socketsMap[meshSocketType];
	}
	else
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMeshSocketType"), true);
		if (EnumPtr)
		{
			FString enumName = EnumPtr->GetNameStringByIndex((int32)meshSocketType);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Not registered MeshSocket: " + enumName));
		}
		return "";
	}
}

bool ACreatureCharacter::GetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform)
{
	if (_socketsMap.Contains(meshSocketType))
	{
		outTransform = GetMesh()->GetSocketTransform(_socketsMap[meshSocketType]);
		return true;
	}
	else
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMeshSocketType"), true);
		if (EnumPtr)
		{
			FString enumName = EnumPtr->GetNameStringByIndex((int32)meshSocketType);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Not registered MeshSocket: " + enumName));
		}
		return false;
	}
}
