// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSystem/MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMyPlayerController::BeginPlay()
{
	//Create Character HUD
	if (CharacterHUDClass != nullptr)
	{
		_characterWidget = CreateWidget<UUserWidget>(this, CharacterHUDClass, "Character HUD");
		if (_characterWidget)
		{
			_characterWidget->AddToViewport(100);
		}
	}
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

	InputComponent->BindAction("Pause", IE_Pressed, this, &AMyPlayerController::TogglePauseMenu);
}

void AMyPlayerController::SetPawn(APawn* newPawn)
{
	Super::SetPawn(newPawn);

	OnPawnChanged.Broadcast(newPawn);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("set pawn"));
}

void AMyPlayerController::_CreateCharacterHud()
{



}

