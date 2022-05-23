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
	FRotator curRotator = GetActionOwner()->GetActorRotation();
	float distXY_Cur_TrackCenter = FVector::Dist2D(curLoc, _trackCenter);

	FVector dirToTrackCenter = (_trackCenter - curLoc).GetSafeNormal();
	float yaw_dirToTrackCenter = dirToTrackCenter.Rotation().Yaw;

	float DeltaAngleH_Forward_ToTrackCenter = FMath::FindDeltaAngleDegrees(curRotator.Yaw, yaw_dirToTrackCenter);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("_trackRadius : %f"), _trackRadius));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("distXY_Cur_TrackCenter : %f"), distXY_Cur_TrackCenter));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("DeltaAngleH_Forward_ToTrackCenter : %f"), DeltaAngleH_Forward_ToTrackCenter));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT(" dirToTrackCenter.Rotation().Yaw : %f"), dirToTrackCenter.Rotation().Yaw));
	DrawDebugLine(GetWorld(), curLoc, _trackCenter, FColor::Blue, false, -1.0f, 0U, 30.0f);
	

	DrawDebugCircle(GetWorld(), FVector(_trackCenter.X, _trackCenter.Y, curLoc.Z), _trackRadius, 10, FColor::Black, false, -1.0f, 0U, 10.0f, FVector::ForwardVector, FVector::RightVector);

	float DistTolerance = 1000;

	if (distXY_Cur_TrackCenter > _trackRadius + DistTolerance)
	{
		_myMovementComp->RotateToYaw(DeltaAngleH_Forward_ToTrackCenter,deltaTime);

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, TEXT("approch "));
	}
	else if (distXY_Cur_TrackCenter < _trackRadius - DistTolerance)
	{
		_myMovementComp->RotateToYaw(FMath::UnwindDegrees(DeltaAngleH_Forward_ToTrackCenter + 180), deltaTime);
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, TEXT("Leave "));
	}
	else
	{
		//GetActionOwner()->GetActorForwardVector().DotProduct()

		float deltaYaw = FMath::FindDeltaAngleDegrees(curRotator.Yaw, yaw_dirToTrackCenter + 90.0f);


		float desiredForwardYaw = yaw_dirToTrackCenter + 90.0f;

		if (FMath::Abs(desiredForwardYaw - curRotator.Yaw) > 1.0f)
		{
			_myMovementComp->RotateToYaw(desiredForwardYaw - curRotator.Yaw, deltaTime);
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, TEXT("forward adjustment "));
		}
		else
		{
			//--------------------------------------
			//v: Velocity
			//w: Yaw Angular Speed
			//R: Track Radius
			//   V = W * R 
			//=> W = V / R 
			//--------------------------------------
			float desiredYawSpeed = (_myMovementComp->GetMaxSpeed() / _trackRadius);
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, FString::Printf(TEXT("desiredYawSpeed: %f"), desiredYawSpeed));
			_myMovementComp->KeepYawSpeed(desiredYawSpeed, deltaTime);
		}

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, TEXT("done!"));
	}
	GetActionOwner()->AddMovementInput(GetActionOwner()->GetActorForwardVector());
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
