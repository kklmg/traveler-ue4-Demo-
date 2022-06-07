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
public:
	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu();

	UFUNCTION(BlueprintCallable)
	void ActivateCharacterStatusUI(bool bActivate);

	UFUNCTION(BlueprintCallable)
	void ActivateControlInfo(bool bActivate);

	UFUNCTION(BlueprintCallable)
	void ToggleControlInfo();

protected:
	virtual void BeginPlay() override;
	void SetupInputComponent() override;
	virtual void SetPawn(APawn* newPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> _pauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> _characterHUDClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUserWidget> _controlInfoWidgetClass;

	UPROPERTY()
	UUserWidget* _controlInfoWidgetIns;

	UPROPERTY()
	UUserWidget* _pauseMenuWidgetIns;

	UPROPERTY()
	UUserWidget* _characterWidgetIns;

	UPROPERTY(BlueprintAssignable)
	FOnPawnChanged OnPawnChanged;

	bool _bShowControlInfo;
};
