// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/StateData.h"

// Sets default values
FStateData::FStateData()
{
	SituationState = ESituationState::ESS_None;
	ActionState = EActionState::EAS_Idle;
	HealthState = EHealthState::EHS_Healthy;
	PostureState = EPostureState::EPS_UpRight;
}
