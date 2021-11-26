// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CreatureAIController.h"

void ACreatureAIController::BeginPlay() 
{
	Super::BeginPlay();
}


void ACreatureAIController::OnPossess(APawn* InPawn) 
{
	Super::OnPossess(InPawn);

	//Run behavior Tree
	if (_behaviorTree)
	{
		RunBehaviorTree(_behaviorTree);
	}
}
void ACreatureAIController::OnUnPossess() 
{
	Super::OnUnPossess();
}
