// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto action : _actions) 
	{
        // process is uninitialized, so initialize it
        if (action->GetState() == EProcessState::UNINITIALIZED)
            action->VInit();

        // give the process an update tick if it's running
        if (action->GetState() == EProcessState::RUNNING)
            action->VUpdate(DeltaTime);

        // check to see if the process is dead
        if (action->IsDead())
        {
            // remove the process
            _actions.Remove(action);
        }
	
	}
	// ...
}