// Fill out your copyright notice in the Description page of Project Settings.


#include "Command/CommandCamera.h"
#include "Camera/CameraComponent.h"



void UCommandCamera::Initialize(UCameraComponent* cameraComponent)
{
	_cameraComponent = cameraComponent;
}