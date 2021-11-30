// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

class UAction;
class UActionData;
class UCharacterActionSet;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRAVELER_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetCharacterState();

	void OnJumpButtonDown();
	void OnJumpButtonUp();

	void OnSprintButtonDown();
	void OnSprintButtonUp();

	void OnDodgeButtonDown();
	void OnDodgeButtonUp();

	void AddMovementInputX(float value);
	void AddMovementInputY(float value);

	void AddToActionProcessPool(UAction* action);
	void ClearActionProcessPool();

	UFUNCTION()
	void OnCharacterStateChanged(ECharacterState characterState);

public:
	UFUNCTION(BlueprintCallable)
	void ExecuteAction(FName actionName);
	UFUNCTION(BlueprintCallable)
	void ExecuteIdle();
	UFUNCTION(BlueprintCallable)
	void ExecuteMove(FVector movement);
	UFUNCTION(BlueprintCallable)
	void ExecuteSprint();
	UFUNCTION(BlueprintCallable)
	void ExecuteJump();
	UFUNCTION(BlueprintCallable)
	void ExecuteAim();
	UFUNCTION(BlueprintCallable)
	void ExecuteDodge();

	UActionData* GetActionData();
	

private:
	void _TickActionProcess(float deltaTime);

private:
	FVector _userMovementInput;

	UPROPERTY()
	TMap<FName, UAction*> _mapActionProcessPool;

	UPROPERTY()
	UActionData* _actionData;

	UPROPERTY(EditDefaultsOnly, Category = ActionSetClasses)
	TMap<TEnumAsByte<ECharacterState>, TSubclassOf<UCharacterActionSet>> _mapActionSet;

	UPROPERTY()
	UCharacterActionSet* _pCurrentActionSet;

	bool _bSprintButtonPress;
};
