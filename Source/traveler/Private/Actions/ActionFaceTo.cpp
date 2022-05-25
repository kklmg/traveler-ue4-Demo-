// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionFaceTo.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameSystem/MyGameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Components/StatusComponent.h"
#include "AIController.h"


UActionFaceTo::UActionFaceTo()
{
	_processName = NSNameAction::FaceTo;
	_actionType = EActionType::EACT_FaceTo;

	_bIsInstantProcess = false;
}

bool UActionFaceTo::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	_myMovementComp = Cast<UMyCharacterMovementComponent>
		(GetActionOwner()->GetComponentByClass(UMyCharacterMovementComponent::StaticClass()));
	if (_myMovementComp == nullptr)
	{
		UE_LOG(LogAction, Warning, TEXT("No My Movement component"));
		return false;
	}

	return true;
}

void UActionFaceTo::VOnExecute()
{
	Super::VOnExecute();

	if (!TryGetRequiredData())
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Direction Data"));
	}
}

void UActionFaceTo::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	if (!TryGetRequiredData())
	{
		SetProcessFailed();
	}

	FVector curLocation = GetActionOwner()->GetActorLocation();
	FRotator curRotation = GetActionOwner()->GetActorRotation();
	
	FVector forward = GetActionOwner()->GetActorForwardVector();

	float yaw_FaceToDir = _faceToDirection.Rotation().Yaw;
	float yaw_Forward = forward.Rotation().Yaw;

	//angle degree between forward and DirectionFaceTo
	float deltaAngleH_Forward_FaceTo = FMath::FindDeltaAngleDegrees(yaw_Forward, yaw_FaceToDir);

	if (FMath::Abs(deltaAngleH_Forward_FaceTo) < 1.0f)
	{
		SetProcessSucceed();
	}

	_myMovementComp->RotateDeltaYaw(deltaAngleH_Forward_FaceTo, deltaTime);
	_myMovementComp->Accelerate(true,deltaTime);
}

void UActionFaceTo::VOnDead()
{
	Super::VOnDead();
}

bool UActionFaceTo::TryGetRequiredData()
{
	return GetActionBlackBoard()->TryGetData_FVector(NSActionData::FaceToDirection::Name,_faceToDirection);
}
