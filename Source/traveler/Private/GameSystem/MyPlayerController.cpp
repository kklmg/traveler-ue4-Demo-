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
	if (_pauseMenuWidgetIns && _pauseMenuWidgetIns->IsInViewport())
	{
		_pauseMenuWidgetIns->RemoveFromParent();
		_pauseMenuWidgetIns = nullptr;

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
	_pauseMenuWidgetIns = CreateWidget<UUserWidget>(this, _pauseMenuClass,"Pause Menu");
	if (_pauseMenuWidgetIns)
	{
		_pauseMenuWidgetIns->AddToViewport(100);

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
		if (_characterHUDClass != nullptr && GetPawn() != nullptr && _characterWidgetIns == nullptr)
		{
			_characterWidgetIns = CreateWidget<UUserWidget>(this, _characterHUDClass, "Character HUD");
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

void AMyPlayerController::ToggleControlInfo()
{
	if (_controlInfoWidgetClass == nullptr) return;

	_bShowControlInfo = !_bShowControlInfo;

	if (_bShowControlInfo)
	{
		if (_controlInfoWidgetIns == nullptr)
		{
			_controlInfoWidgetIns = CreateWidget<UUserWidget>(this, _controlInfoWidgetClass, "ControlInfoWidget");
			check(_controlInfoWidgetIns)
		}

		if (_controlInfoWidgetIns->IsInViewport() == false)
		{
			_controlInfoWidgetIns->AddToViewport(100);
		}
	}
	else
	{
		if (_controlInfoWidgetIns)
		{
			_controlInfoWidgetIns->RemoveFromViewport();
		}
	}
}

