// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/Action.h"
#include "State/CharacterStateBase.h"
#include "Character/MyCharacter.h"
#include "Components/PawnCameraComponent.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


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

	_actionData = NewObject<UActionData>(this);
	
	// ...

	//Get Character
	ACharacter* character = Cast<ACharacter>(GetOwner());
	check(character != nullptr);

	UCharacterMovementComponent* movementComp = character->GetCharacterMovement();
	check(movementComp != nullptr);
	
	//set Action Group
	OnCharacterMovementModeChanged(character, EMovementMode::MOVE_None, 0);

	//bind MovementModeChanged event
	character->MovementModeChangedDelegate.AddDynamic(this, &UActionComponent::OnCharacterMovementModeChanged);

	


	if (DefaultCharacterStateClass != nullptr)
	{
		_pCurrentCharacterState = NewObject<UCharacterStateBase>(this, DefaultCharacterStateClass);
		_pCurrentCharacterState->Initialize(character);
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

	_TickActionProcess(DeltaTime);
}

void UActionComponent::SetCharacterState()
{
}
void UActionComponent::TriggerIdle()
{
	if (_pCurrentCharacterState != nullptr)
	{
		_pCurrentCharacterState->Idle(this);
	}
}
void UActionComponent::TriggerMove()
{
	if (_pCurrentCharacterState != nullptr)
	{
		_pCurrentCharacterState->Move(this);
	}
}
void UActionComponent::TriggerSprint()
{
	if (_pCurrentCharacterState != nullptr)
	{
		_pCurrentCharacterState->Sprint(this);
	}
}
void UActionComponent::TriggerJump()
{
	if (_pCurrentCharacterState != nullptr)
	{
		_pCurrentCharacterState->Jump(this);
	}
}
void UActionComponent::TriggerTarget()
{
	if (_pCurrentCharacterState != nullptr)
	{
		_pCurrentCharacterState->Target(this);
	}
}
void UActionComponent::TriggerDash() 
{
	if (_pCurrentCharacterState != nullptr)
	{
		_pCurrentCharacterState->Dash(this);
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
	if (action != nullptr)
	{
		_mapActionProcessPool.Add(action->GetActionName(), action);
	}
}

void UActionComponent::_TickActionProcess(float deltaTime)
{
	TArray<UAction*> finieshedActions;
	
	for (auto pair : _mapActionProcessPool)
	{
		pair.Value->VUpdate(deltaTime, GetOwner(), _actionData);

		if (pair.Value->GetState() == EActionState::AS_FINISHED)
		{
			finieshedActions.Add(pair.Value);
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, pair.Value->GetName());
	}

	for (auto action : finieshedActions)
	{
		_mapActionProcessPool.Remove(action->GetActionName());
	}


	//_MapActionsInProgress.Compact();

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

void UActionComponent::OnJumpButtonDown()
{
	TriggerJump();
}

void UActionComponent::OnJumpButtonUp()
{

}

void UActionComponent::OnSprintButtonDown()
{
	_bSprintButtonPress = true;

	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(GetOwner());
	check(pCharacter != nullptr);

	pCharacter->GetCharacterMovement()->MaxWalkSpeed = pCharacter->GetAttributeComponent()->GetRunSpeed();
}

void UActionComponent::OnSprintButtonUp()
{
	_bSprintButtonPress = false;

	//Get My Character
	AMyCharacter* pCharacter = Cast<AMyCharacter>(GetOwner());
	check(pCharacter != nullptr);

	pCharacter->GetCharacterMovement()->MaxWalkSpeed = pCharacter->GetAttributeComponent()->GetWalkSpeed();
}


void UActionComponent::ExecuteAction(FName actionName)
{
	UAction* action;

	if (_pCurrentCharacterState->TryGetActionInstance(actionName, &action))
	{
		action->Start(this);

		if (action->IsInstantAction()) 
		{
			if (_mapActionProcessPool.Contains(actionName) )
			{
			}
		}
	}
}

void UActionComponent::OnCharacterMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode) 
{
	UCharacterMovementComponent* movementComp = Character->GetCharacterMovement();
	check(movementComp != nullptr);

	if (_mapActionGroup.Contains(movementComp->MovementMode)) 
	{
		//clear process pool
		ClearActionProcessPool();

		//Instaciate Action Group Class
		TSubclassOf<UCharacterStateBase> ActionGroupClass = _mapActionGroup[movementComp->MovementMode];
		UCharacterStateBase* actionGroupIns = NewObject<UCharacterStateBase>(ActionGroupClass);

		//initialize Action Group
		actionGroupIns->Initialize(Character);
		actionGroupIns->Enter();

		//Set Current Action Group
		_pCurrentCharacterState->MarkPendingKill();
		_pCurrentCharacterState = actionGroupIns;
	}
}

void UActionComponent::ClearActionProcessPool()
{
	for (auto pair : _mapActionProcessPool)
	{
		pair.Value->Abort();
	}
	_mapActionProcessPool.Empty();
}

