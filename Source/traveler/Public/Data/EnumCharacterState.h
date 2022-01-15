// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_GroundNormal UMETA(DisplayName = "GroundNormal"),
	ECS_GroundDodging UMETA(DisplayName = "GroundDodging"),
	ECS_AirFalling UMETA(DisplayName = "AirFalling"),
	ECS_AirNormal UMETA(DisplayName = "AirNormal"),
	ECS_AirFlying UMETA(DisplayName = "AirFlying"),
	ECS_Swimming UMETA(DisplayName = "Swimming"),
	ECS_Stunning UMETA(DisplayName = "Stunning"),
};