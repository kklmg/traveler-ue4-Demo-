// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CreatureAIController.h"

void ACreatureAIController::BeginPlay() 
{
	if (_behaviorTree) 
	{
		RunBehaviorTree(_behaviorTree);
	}
}
