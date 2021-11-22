// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, newPawn);

/**
 * 
 */
UCLASS()
class TRAVELER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
private:

	virtual void BeginPlay() override;

	void SetupInputComponent() override;

	virtual void SetPawn(APawn* newPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> CharacterHUDClass;

	UPROPERTY()
	UUserWidget* _pauseMenuWidget;

	UPROPERTY()
	UUserWidget* _characterWidget;

	UPROPERTY(BlueprintAssignable)
	FOnPawnChanged OnPawnChanged;

public:
	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu();

};
