// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

/**
 * 
 */
 class UEventDataBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEventPublished, UEventDataBase*);