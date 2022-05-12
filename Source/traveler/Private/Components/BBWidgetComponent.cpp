// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BBWidgetComponent.h"

UBBWidgetComponent::UBBWidgetComponent()
{
	_bFaceToCamera = true;
}

void UBBWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(_bFaceToCamera && GetWorld()->GetFirstPlayerController())
	{
		APlayerCameraManager* cameraMng = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		if (cameraMng) 
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, cameraMng->GetCameraRotation().ToString());
			FRotator widgetRotator(cameraMng->GetCameraRotation());
			widgetRotator.Pitch = 0;
			widgetRotator.Roll = 0;
			widgetRotator.Yaw = widgetRotator.Yaw + 180.0f;
			SetWorldRotation(widgetRotator);
		}
	}
}
