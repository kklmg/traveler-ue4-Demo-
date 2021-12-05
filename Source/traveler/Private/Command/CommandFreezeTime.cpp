// Fill out your copyright notice in the Description page of Project Settings.


#include "Command/CommandFreezeTime.h"
#include "Kismet/GameplayStatics.h"

   
void UCommandFreezeTime::VExecute()
{
	if (_actor) 
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1); //Global slow motion.
		_actor->CustomTimeDilation = 10; // Individual slow motion.
	}
}

void UCommandFreezeTime::VUndo() 
{
	if (_actor)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1); //Global slow motion.
		_actor->CustomTimeDilation = 1; // Individual slow motion.
	}
}