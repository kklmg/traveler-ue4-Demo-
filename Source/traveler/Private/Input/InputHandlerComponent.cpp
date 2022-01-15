// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandlerComponent.h"

// Sets default values for this component's properties
UInputHandlerComponent::UInputHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInputHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInputHandlerComponent::VGoForward()
{
}

void UInputHandlerComponent::VGoRight()
{
}

void UInputHandlerComponent::VCameraPitch()
{
}

void UInputHandlerComponent::VCameraYaw()
{
}

void UInputHandlerComponent::VCameraZoomInOut()
{
}

void UInputHandlerComponent::VPressButtonJump()
{
}

void UInputHandlerComponent::VReleaseButtonJump()
{
}

void UInputHandlerComponent::VPressButtonSprint()
{
}

void UInputHandlerComponent::VReleaseButtonSprint()
{
}

void UInputHandlerComponent::VPressButtonDodge()
{
}

void UInputHandlerComponent::VReleaseButtonDodge()
{
}

void UInputHandlerComponent::VPressButtonFire()
{
}

void UInputHandlerComponent::VReleaseButtonFire()
{
}

void UInputHandlerComponent::VPressButtonAim()
{
}

void UInputHandlerComponent::VReleaseButtonAim()
{
}

void UInputHandlerComponent::VPressButtonAction1()
{
}

void UInputHandlerComponent::VReleaseButtonAction1()
{
}

void UInputHandlerComponent::VPressButtonAction2()
{
}

void UInputHandlerComponent::VReleaseButtonAction2()
{
}

void UInputHandlerComponent::VPressButtonAction3()
{
}

void UInputHandlerComponent::VReleaseButtonAction3()
{
}

void UInputHandlerComponent::VPressButtonAction4()
{
}

void UInputHandlerComponent::VReleaseButtonAction4()
{
}

void UInputHandlerComponent::OnCharacterStateChanged(ECharacterState characterState)
{
}

