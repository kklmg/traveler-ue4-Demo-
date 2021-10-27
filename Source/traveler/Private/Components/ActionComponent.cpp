// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/Action.h"
//#include "Actions/ActionData.h"
#include "State/CharacterStateBase.h"
#include "Character/MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AttributeComponent.h"


// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_actionData = NewObject<UActionData>();
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (DefaultCharacterState != nullptr) 
	{
		_pCharacterState = DefaultCharacterState.GetDefaultObject();
		this->TriggerIdle();
	}
	
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_movementInput.IsZero() == false) 
	{
		_actionData->Direction = _CalculateMovingDirection();
		this->TriggerMove();
	}

	_LoopActions(DeltaTime);
}

void UActionComponent::SetCharacterState()
{
}
void UActionComponent::TriggerIdle()
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Idle(this);
	}
}
void UActionComponent::TriggerMove()
{
	if (_pCharacterState != nullptr) 
	{
		_pCharacterState->Move(this);
	}
}
void UActionComponent::TriggerSprint()
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Sprint(this);
	}
}
void UActionComponent::TriggerJump()
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Jump(this);
	}
}
void UActionComponent::TriggerTarget()
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Target(this);
	}
}
void UActionComponent::TriggerDash() 
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Dash(this);
	}
}

void UActionComponent::AddMovementInputX(float value) 
{
	_movementInput.X = value;
}
void UActionComponent::AddMovementInputY(float value) 
{
	_movementInput.Y = value;
}

void UActionComponent::AddToLoop(UAction* action)
{
	_MapActionsInProgress.Add(action->GetActionName(),action);
}

void UActionComponent::_LoopActions(float deltaTime)
{
	for (auto pair : _MapActionsInProgress)
	{
		pair.Value->VUpdate(deltaTime, GetOwner(), _actionData);

		if (pair.Value->GetState() == EActionState::AS_FINISHED)
		{
			_MapActionsInProgress.FindAndRemoveChecked(pair.Key);
		}
	}

	//int count = _MapActionsInProgress.Num();
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::FromInt(count));
}

FVector UActionComponent::_CalculateMovingDirection()
{
	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(GetOwner());
	check(pCharacter != nullptr);

	//Get Camera
	UCameraComponent* pCamera = pCharacter->GetCameraComponent();
	check(pCamera != nullptr);

	//Get Attribute
	UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
	check(pAttributeComponent != nullptr);

	//Get Input Direction
	FVector inputDirection(_movementInput.X, _movementInput.Y, 0);

	//Get Camera Rotation Matrix
	FRotator cameraRotator = pCamera->GetComponentRotation();
	FMatrix cameraRotationMatrix = FRotationMatrix(cameraRotator);

	//Calculate moving direction
	FVector moveDirection = cameraRotationMatrix.TransformVector(inputDirection);
	moveDirection.Z = 0;
	moveDirection.Normalize();

	return moveDirection;
}

UActionData* UActionComponent::GetActionData()
{
	return _actionData;
}