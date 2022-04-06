// Fill out your copyright notice in the Description page of Project Settings.


#include "Status/StatusTableRow.h"

bool FStatusTableRow::IsBasicStatus()
{
	switch (StatusType)
	{
		case EStatusType::EStatus_Health:
		case EStatusType::EStatus_Mana:
		case EStatusType::EStatus_Stamina:
		case EStatusType::EStatus_Energy:
		{ 
			return true; 
		}break;
		case EStatusType::EStatus_Strength:
		case EStatusType::EStatus_Defence:
		case EStatusType::EStatus_WalkingSpeed:
		case EStatusType::EStatus_SprintingSpeed:	
		case EStatusType::EStatus_FlyingSpeed:
		default:
		{
			return false;
		}
		break;
	}
}
