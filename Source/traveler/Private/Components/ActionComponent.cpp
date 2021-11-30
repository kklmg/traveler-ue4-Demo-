// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActionComponent.h"
#include "Actions/Action.h"
#include "Actions/CharacterActionSet.h"
#include "Character/HumanCharacter.h"
#include "Components/PawnCameraComponent.h"
#include "Components/AttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameSystem/MyBlueprintFunctionLibrary.h"


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
	ACreatureCharacter* character = GetOwner<ACreatureCharacter>();
	check(character != nullptr);
	
	OnCharacterStateChanged(character->GetCharacterState());

	//bind Character changed event
	character->OnCharacterStateChangedDelegate.AddDynamic(this, &UActionComponent::OnCharacterStateChanged);
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AHumanCharacter* character = GetOwner<AHumanCharacter>();

	if (character && character->IsPlayerControlled() && _userMovementInput.IsZero() == false)
	{
		//Get Camera
		UCameraComponent* cameraComp = character->GetCameraComponent();
		check(cameraComp != nullptr);

		ExecuteMove(UMyBlueprintFunctionLibrary::InptAxisToCameraDirection(_userMovementInput, cameraComp));
	}

	_TickActionProcess(DeltaTime);
}

void UActionComponent::SetCharacterState()
{
}

void UActionComponent::ExecuteAction(FName actionName)
{
	if (_pCurrentActionSet == nullptr || _mapActionProcessPool.Contains(actionName))
	{
		return;
	}

	UAction* action;

	if (_pCurrentActionSet->TryGetActionInstance(actionName, &action))
	{
		action->Abort();
		action->Initialize(this, _actionData);
		action->VExecute();

		if (action->IsInstantAction() == false)
		{
			AddToActionProcessPool(action);
		}
	}
}
void UActionComponent::ExecuteIdle()
{
	ExecuteAction(ActionName::IDLE);
}
void UActionComponent::ExecuteMove(FVector movement)
{
	_actionData->SetMovementInput(movement);
	ExecuteAction(ActionName::MOVE);
}
void UActionComponent::ExecuteSprint()
{
	ExecuteAction(ActionName::SPRINT);
}
void UActionComponent::ExecuteJump()
{
	ExecuteAction(ActionName::JUMP);
}
void UActionComponent::ExecuteAim()
{
	ExecuteAction(ActionName::AIM);
}
void UActionComponent::ExecuteDodge()
{
	ExecuteAction(ActionName::DODGE);
}

void UActionComponent::AddMovementInputX(float value) 
{
	_userMovementInput.X = value;
}
void UActionComponent::AddMovementInputY(float value) 
{
	_userMovementInput.Y = value;
}

void UActionComponent::AddToActionProcessPool(UAction* action)
{
	if (action == nullptr) return;

	_mapActionProcessPool.Add(action->GetActionName(), action);
}

void UActionComponent::_TickActionProcess(float deltaTime)
{
	TArray<FName> finieshedActionKeys;

	//find out all finished actions
	for (auto pair : _mapActionProcessPool)
	{
		EActionState actionState = pair.Value->GetState();
		if (actionState == EActionState::AS_Finished || actionState == EActionState::AS_Aborted)
		{
			finieshedActionKeys.Add(pair.Key);
		}
	}

	//remove all finished actions
	for (auto key : finieshedActionKeys)
	{
		_mapActionProcessPool.Remove(key);
	}

	//tick actions
	for (auto pair : _mapActionProcessPool)
	{
		pair.Value->VTick(deltaTime);
	}
}

UActionData* UActionComponent::GetActionData()
{
	return _actionData;
}

void UActionComponent::OnJumpButtonDown()
{
	ExecuteJump();
}

void UActionComponent::OnJumpButtonUp()
{

}

void UActionComponent::OnSprintButtonDown()
{
	_bSprintButtonPress = true;

	//Get My Character
	AHumanCharacter* humanCharacter = Cast<AHumanCharacter>(GetOwner());
	check(humanCharacter != nullptr);

	humanCharacter->GetCharacterMovement()->MaxWalkSpeed = humanCharacter->GetAttributeComponent()->GetRunSpeed();
}

void UActionComponent::OnSprintButtonUp()
{
	_bSprintButtonPress = false;

	//Get My Character
	AHumanCharacter* humanCharacter = Cast<AHumanCharacter>(GetOwner());
	check(humanCharacter != nullptr);

	humanCharacter->GetCharacterMovement()->MaxWalkSpeed = humanCharacter->GetAttributeComponent()->GetWalkSpeed();
}

void UActionComponent::OnDodgeButtonDown() 
{
	ExecuteDodge();
}
void UActionComponent::OnDodgeButtonUp() 
{
}

void UActionComponent::OnCharacterStateChanged(ECharacterState characterState)
{
	ACreatureCharacter* character = GetOwner<ACreatureCharacter>();
	check(character != nullptr);

	if (_mapActionSet.Contains(characterState))
	{
		//clear process pool
		ClearActionProcessPool();

		//Make instace of ActionSetClass
		TSubclassOf<UCharacterActionSet> actionSetClass = _mapActionSet[characterState];

		UCharacterActionSet* actionSetIns = actionSetClass ? 
			NewObject<UCharacterActionSet>(this, actionSetClass) 
			: NewObject<UCharacterActionSet>(this);

			actionSetIns->VEnter();
		

		//Set Current Action set
		if (_pCurrentActionSet != nullptr)
		{
			_pCurrentActionSet->VLeave();
			_pCurrentActionSet->MarkPendingKill();
		}
		_pCurrentActionSet = actionSetIns;
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

