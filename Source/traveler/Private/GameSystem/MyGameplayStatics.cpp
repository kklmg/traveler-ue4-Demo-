// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyGameplayStatics.h"
#include "Camera/CameraComponent.h"

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

EDamageType UMyGameplayStatics::StatusEffectTypeToDamageType(EStatusEffect statusEffectType)
{
	switch (statusEffectType)
	{
	case EStatusEffect::EStatusEffect_NONE: return EDamageType::EDamage_None;
		break;
	case EStatusEffect::EStatusEffect_Fire: return EDamageType::EDamage_Fire;
		break;
	case EStatusEffect::EStatusEffect_Water: return EDamageType::EDamage_Water;
		break;
	case EStatusEffect::EStatusEffect_Ice: return EDamageType::EDamage_Ice;
		break;
	case EStatusEffect::EStatusEffect_Electricity: return EDamageType::EDamage_Electricity;
		break;
	case EStatusEffect::EStatusEffect_Poison: return EDamageType::EDamage_Poison;
		break;
	case EStatusEffect::EStatusEffect_Stun: return EDamageType::EDamage_None;
		break;
	default: return EDamageType::EDamage_None;
		break;
	}
}
//
//float UMyGameplayStatics::CalculateDamage(float basicDamage, EDamageType damageType, AActor* damageGiver, AActor* damageReceiver)
//{
//	return 0.0f;
//}

