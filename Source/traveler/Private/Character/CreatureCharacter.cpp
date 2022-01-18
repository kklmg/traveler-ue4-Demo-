// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CreatureCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/ActionComponent.h"
#include "Data/CharacterAttribute.h"
#include "Components/AttributeComponent.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/BillBoardWidgetComponent.h"
#include "Components/AnimationEventComponent.h"
#include "Input/InputHandlerComponent.h"


// Sets default values
ACreatureCharacter::ACreatureCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create action component
	if (_actionComponent == nullptr)
	{
		_actionComponent = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
		check(_actionComponent != nullptr);
	}

	//Create Attribute component
	if (_attributeComponent == nullptr)
	{
		_attributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
		check(_attributeComponent != nullptr);
	}

	//Create billboard component
	if (_billboardWidgetComponent == nullptr)
	{
		_billboardWidgetComponent = CreateDefaultSubobject<UBillBoardWidgetComponent>(TEXT("BillBoardWidgetComponent"));
		check(_billboardWidgetComponent != nullptr);
	}

	if (_animationEventComponent == nullptr)
	{
		_animationEventComponent = CreateDefaultSubobject<UAnimationEventComponent>(TEXT("AnimationEventComponent"));
		check(_billboardWidgetComponent != nullptr);
	}


	if (_inputHandlerComponent == nullptr)
	{
		_inputHandlerComponent = CreateDefaultSubobject<UInputHandlerComponent>(TEXT("InputHandlerComponent"));
		check(_inputHandlerComponent != nullptr);
	}

	bUseControllerRotationYaw = false;

	_characterState = ECharacterState::ECS_GroundNormal;
}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();

	MovementModeChangedDelegate.AddDynamic(this, &ACreatureCharacter::OnCharacterMovementModeChanged);
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

	if(_inputHandlerComponent)
	{
		_inputHandlerComponent->BindInputs(PlayerInputComponent);
	}
}

float ACreatureCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);


	//GetAttributeComponent()->SetHealth();
	_attributeComponent->SetAttributeChange(EAttributeType::EATT_Health, -actualDamage);

	_billboardWidgetComponent->ShowWidget(EWidgetType::WT_HealthBar);

	GEngine->AddOnScreenDebugMessage(-1, -5, FColor::Red, "TakeDamage: " + FString::SanitizeFloat(actualDamage));

	return actualDamage;
}

FORCEINLINE UAttributeComponent* ACreatureCharacter::GetAttributeComponent()
{
	return _attributeComponent;
}

FORCEINLINE UAnimationEventComponent* ACreatureCharacter::GetAanimationEventComponent()
{
return _animationEventComponent;
}

FORCEINLINE UCharacterAttribute* ACreatureCharacter::VGetAttribute(EAttributeType attributeType)
{
	return _attributeComponent->GetAttribute(attributeType);
}

bool ACreatureCharacter::VSetAttribute(EAttributeType attributeType, float newValue)
{
	return _attributeComponent->SetAttribute(attributeType, newValue);
}

bool ACreatureCharacter::VSetAttributeChange(EAttributeType attributeType, float deltaValue)
{
	return _attributeComponent->SetAttributeChange(attributeType, deltaValue);
}

FORCEINLINE UActionComponent* ACreatureCharacter::GetActionComponent()
{
	return _actionComponent;
}

UActionBase* ACreatureCharacter::VExecuteAction(EActionType actionType)
{
	if (_actionComponent) 
	{
		return _actionComponent->ExecuteAction(actionType);
	}
	return nullptr;
}


FORCEINLINE UActionBlackBoard* ACreatureCharacter::VGetActionBlackBoard()
{
	return _actionComponent->GetActionBlackBoard();
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


void ACreatureCharacter::SetCharacterState(ECharacterState characterState) 
{
	if (_characterState != characterState) 
	{
		_characterState = characterState;
		OnCharacterStateChangedDelegate.Broadcast(_characterState);
	}
}

FORCEINLINE ECharacterState ACreatureCharacter::GetCharacterState()
{
	return _characterState;
}


void ACreatureCharacter::OnCharacterMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	EMovementMode curMovementMode = GetCharacterMovement()->MovementMode;

	switch (curMovementMode)
	{
	case MOVE_None: 
		break;
	case MOVE_Walking: SetCharacterState(ECharacterState::ECS_GroundNormal);
		break;
	case MOVE_NavWalking:
		break;
	case MOVE_Falling: SetCharacterState(ECharacterState::ECS_AirFalling);
		break;
	case MOVE_Swimming:SetCharacterState(ECharacterState::ECS_Swimming);
		break;
	case MOVE_Flying: SetCharacterState(ECharacterState::ECS_AirFlying);
		break;
	case MOVE_Custom:
		break;
	case MOVE_MAX:
		break;
	default:
		break;
	}
}