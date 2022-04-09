// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyGameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Damage/DamageHandlerInterface.h"
#include "Damage/DamageData.h"


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
//
//EElementalType UMyGameplayStatics::StatusEffectTypeToDamageType(EStatusEffect statusEffectType)
//{
//	switch (statusEffectType)
//	{
//	case EStatusEffect::EElemental_NONE: return EElementalType::EDamage_None;
//		break;
//	case EStatusEffect::EElemental_Fire: return EElementalType::EDamage_Fire;
//		break;
//	case EStatusEffect::EElemental_Water: return EElementalType::EDamage_Water;
//		break;
//	case EStatusEffect::EElemental_Ice: return EElementalType::EDamage_Ice;
//		break;
//	case EStatusEffect::EElemental_Electricity: return EElementalType::EDamage_Electricity;
//		break;
//	case EStatusEffect::EElemental_Poison: return EElementalType::EDamage_Poison;
//		break;
//	case EStatusEffect::EElemental_Stun: return EElementalType::EDamage_None;
//		break;
//	default: return EElementalType::EDamage_None;
//		break;
//	}
//}

bool UMyGameplayStatics::CauseDamage(AActor* damagedActor, UDamageData* damageData, FVector impactPoint, AActor* causer, APawn* instigator)
{
	if(!damagedActor) return false;
	if (!damageData) return false;

	IDamageHandlerInterface* damageHandlerInterface = Cast<IDamageHandlerInterface>(damagedActor);
	if(damageHandlerInterface)
	{
		damageHandlerInterface->VHandleDamageData(damageData,impactPoint,causer, instigator);
	}

	else
	{
		UGameplayStatics::ApplyDamage(damagedActor, damageData->Damage, instigator ? instigator->GetController() : nullptr, causer, damageData->DamageTypeClass);
	}

	return true;
}
//
//float UMyGameplayStatics::CalculateDamage(float basicDamage, EDamageType damageType, AActor* damageGiver, AActor* damageReceiver)
//{
//	return 0.0f;
//}

