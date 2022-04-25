// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyGameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/DamageHandlerComponent.h"
#include "Damage/DamageHandlerInterface.h"



FVector UMyGameplayStatics::InptAxisToCameraDirection(FVector inputAxis, UCameraComponent* cameraComp)
{
	//Get Camera Rotation Matrix
	FRotator cameraRotator = cameraComp->GetComponentRotation();


	FVector moveDirection = cameraRotator.RotateVector(inputAxis);
	moveDirection.Z = 0;
	moveDirection.Normalize();

	return moveDirection;
}

float UMyGameplayStatics::ComputeDistance(FVector from, FVector to, EPlane plane /*= Plane_None*/)
{
	FVector dirFromTo = to - from;

	switch (plane)
	{
	case Plane_None:
	{
		return dirFromTo.Size();
	}
	break;
	case Plane_XY:
	{
		dirFromTo.Z = 0;
		dirFromTo.Size();
	}
	break;
	case Plane_XZ:
	{
		dirFromTo.Y = 0;
		dirFromTo.Size();
	}
	break;
	case Plane_YZ:
	{
		dirFromTo.X = 0;
		dirFromTo.Size();
	}
	break;
	}

	return dirFromTo.Size();
}

bool UMyGameplayStatics::CauseDamage(AActor* damagedActor, FDamageData& damageData, FVector impactPoint, AActor* causer, APawn* instigator)
{
	if (!damagedActor) return false;

	UDamageHandlerComponent* damageHandlerComp = 
		Cast<UDamageHandlerComponent>(damagedActor->GetComponentByClass(UDamageHandlerComponent::StaticClass()));

	if (damageHandlerComp)
	{
		damageHandlerComp->HandleDamageData(damageData, impactPoint, causer, instigator);
	}

	else
	{
		UGameplayStatics::ApplyDamage(damagedActor, damageData.Damage, instigator ? instigator->GetController() : nullptr, causer, damageData.DamageTypeClass);
	}

	return true;
}
