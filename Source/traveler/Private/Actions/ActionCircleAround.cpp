// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ActionCircleAround.h"
#include "Actions/ActionData/ActionBlackBoard.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MyCharacterMovementComponent.h"
#include "Character/CreatureCharacter.h"
#include "Components/StatusComponent.h"
#include "DrawDebugHelpers.h"

UActionCircleAround::UActionCircleAround()
{
	_processName = NSNameAction::FlyAroundPoint;
	_actionType = EActionType::EACT_FlyAround;

	_bIsInstantProcess = false;
}

bool UActionCircleAround::VCanExecute()
{
	if (!Super::VCanExecute()) return false;

	if (!TryGetRequiredData())
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Action Data"));
		return false;
	}

	_myMovementComp = Cast<UMyCharacterMovementComponent>
		(GetActionOwner()->GetComponentByClass(UMyCharacterMovementComponent::StaticClass()));
	if (_myMovementComp == nullptr)
	{
		SetProcessFailed();
		UE_LOG(LogAction, Warning, TEXT("Fly to: No Movement component"));
		return false;
	}

	return true;
}

void UActionCircleAround::VOnExecute()
{
	Super::VOnExecute();
}

void UActionCircleAround::VOnTick(float deltaTime)
{
	Super::VOnTick(deltaTime);

	//Update data
	TryGetRequiredData();

	FVector curLoc = GetActionOwner()->GetActorLocation();
	float distXY_Cur_TrackCenter = FVector::Dist2D(curLoc, _trackCenter);

	FVector dirToTrackCenter = (_trackCenter - curLoc).GetSafeNormal();
	float DeltaAngleH_Forward_ToTrackCenter= FMath::FindDeltaAngleDegrees(GetActionOwner()->GetActorRotation().Yaw, dirToTrackCenter.Rotation().Yaw);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("distXY_Cur_TrackCenter : %f"), distXY_Cur_TrackCenter));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("DeltaAngleH_Forward_ToTrackCenter : %f"), DeltaAngleH_Forward_ToTrackCenter));

	float DistTolerance = 1000;


	if (distXY_Cur_TrackCenter > _trackRadius + DistTolerance)
	{
		_myMovementComp->RotateToYaw(DeltaAngleH_Forward_ToTrackCenter,deltaTime);

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("approch "));
	}
	else if (distXY_Cur_TrackCenter < _trackRadius - DistTolerance)
	{
		_myMovementComp->RotateToYaw(DeltaAngleH_Forward_ToTrackCenter + 180, deltaTime);
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("Leave "));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TEXT("done!"));
	}
	//GetActionOwner()->AddMovementInput(GetActionOwner()->GetActorForwardVector());

	//--------------------------------------
	//v: Velocity
	//w: Yaw Angular Speed
	//R: Track Radius
	//   V = W * R 
	//=> W = V / R 
	//--------------------------------------
	float desiredYawSpeed = _trackRadius / _myMovementComp->GetMaxSpeed();
}

bool UActionCircleAround::TryGetRequiredData()
{

	if (GetActionBlackBoard()->TryGetData_Float(NSActionData::TrackRadius::Name, _trackRadius) &&
		GetActionBlackBoard()->TryGetData_FVector(NSActionData::TrackCenter::Name, _trackCenter))
	{
	
		return true;
	}
	else
	{
		return false;
	}
}
