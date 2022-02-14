// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/StateData.h"

// Sets default values
FStateData::FStateData()
{
	AnimationState = EAnimationState::EAnimState_None;
	SituationState = ESituationState::ESS_None;
	HealthState = EHealthState::EHS_Healthy;
	PostureState = EPostureState::EPS_UpRight;
}
