// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStateBase.h"
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "AttributeComponent.h"
#include "ActionComponent.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_movementInput.IsZero() == false) 
	{
		//Get My Character
		AMyCharacter* pCharacter = Cast<AMyCharacter>(GetOwner());
		check(pCharacter != nullptr);

		UCameraComponent* pCamera = pCharacter->GetCameraComponent();
		check(pCamera != nullptr);

		UAttributeComponent* pAttributeComponent = pCharacter->GetAttributeComponent();
		check(pAttributeComponent != nullptr);

		FVector inputDirection(_movementInput.X, _movementInput.Y, 0);

		FRotator cameraRotator = pCamera->GetComponentRotation();
		FMatrix cameraRotationMatrix = FRotationMatrix(cameraRotator);

		FVector moveDirection = cameraRotationMatrix.TransformVector(inputDirection);
		moveDirection.Z = 0;
		moveDirection.Normalize();

		pCharacter->SetActorRotation(moveDirection.Rotation());
		pCharacter->AddMovementInput(moveDirection, pAttributeComponent->GetVelocity()*DeltaTime);
	}

	UpdateActions(DeltaTime);
}

void UActionComponent::SetState()
{
}
void UActionComponent::Move(FVector direction, float scale)
{
	if (_pCharacterState != nullptr) 
	{
		_pCharacterState->Move();
	}
}
void UActionComponent::Sprint() 
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Sprint();
	}
}
void UActionComponent::Jump() 
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Jump();
	}
}
void UActionComponent::Target() 
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Target();
	}
}
void UActionComponent::Dash() 
{
	if (_pCharacterState != nullptr)
	{
		_pCharacterState->Dash();
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

void UActionComponent::StartAction(UAction* action)
{
	if (action == nullptr || action->CanStart() == false) return;

	action->Start();
	_MapActionsInProgress.Add(action->GetActionName(),action);
}

void UActionComponent::UpdateActions(float deltaTime)
{
	for (auto pair : _MapActionsInProgress)
	{
		pair.Value->VUpdate(deltaTime);

		if (pair.Value->GetState() == EActionState::AS_FINISHED) 
		{
			_MapActionsInProgress.FindAndRemoveChecked(pair.Key);
		}
	}
}