// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EProcessState : uint8
{
	EPS_None UMETA(DisplayName = "None"),

	EPS_UnInitialized UMETA(DisplayName = "UnInitialized"),
	EPS_ReadyToExecute UMETA(DisplayName = "ReadyToExecute"),
	// Living processes
	EPS_Running UMETA(DisplayName = "Running"),  // initialized and running
	EPS_Paused UMETA(DisplayName = "Paused"),  // initialized but paused

	// Dead processes
	EPS_SUCCEEDED UMETA(DisplayName = "SUCCEEDED"),  // execution succeed
	EPS_FAILED UMETA(DisplayName = "FAILED"),  // execution failed 
	EPS_Aborted UMETA(DisplayName = "Aborted"),
};