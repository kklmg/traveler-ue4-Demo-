// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Input/InputBindingNames.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::TogglePauseMenu()
{
	//Hide Pause Menu
	if (_pauseMenuWidget && _pauseMenuWidget->IsInViewport())
	{
		_pauseMenuWidget->RemoveFromParent();
		_pauseMenuWidget = nullptr;

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());

		// Single player only
		if (GetWorld()->IsNetMode(NM_Standalone))
		{
			UGameplayStatics::SetGamePaused(this, false);
		}

		return;
	}

	//Show Pause Menu
	_pauseMenuWidget = CreateWidget<UUserWidget>(this, PauseMenuClass,"Pause Menu");
	if (_pauseMenuWidget)
	{
		_pauseMenuWidget->AddToViewport(100);

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());

		// Single-player only
		if (GetWorld()->IsNetMode(NM_Standalone))
		{
			UGameplayStatics::SetGamePaused(this, true);
		}
	}
}


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(NSInputBindingName::Pause, IE_Pressed, this, &AMyPlayerController::TogglePauseMenu);

#if WITH_EDITOR
	
#else
	InputComponent->BindAction(NSInputBindingName::ESC, IE_Pressed, this, &AMyPlayerController::TogglePauseMenu);
#endif

}

void AMyPlayerController::SetPawn(APawn* newPawn)
{
	Super::SetPawn(newPawn);
	OnPawnChanged.Broadcast(newPawn);
}

void AMyPlayerController::ActivateCharacterStatusUI(bool bActivate)
{
	if(bActivate)
	{
		if (CharacterHUDClass != nullptr && GetPawn() != nullptr && _characterWidgetIns == nullptr)
		{
			_characterWidgetIns = CreateWidget<UUserWidget>(this, CharacterHUDClass, "Character HUD");
			check(_characterWidgetIns)
			_characterWidgetIns->AddToViewport(100);
		}
	}
	else
	{
		if(_characterWidgetIns)
		{
			_characterWidgetIns->MarkPendingKill();
			_characterWidgetIns = nullptr;
		}
	}
}

