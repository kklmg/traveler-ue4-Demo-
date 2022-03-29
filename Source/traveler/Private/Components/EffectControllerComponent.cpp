// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EffectControllerComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UEffectControllerComponent::UEffectControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEffectControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetUpMaterialInsDynamic(0);
}

void UEffectControllerComponent::PlayEffect(EStatusEffect effectType)
{
	if(_MID)
	{
		//test code
		_MID->SetVectorParameterValue(FName("da"), FLinearColor(1, 1, 1, 1));
	}
}

void UEffectControllerComponent::StopEffect(EStatusEffect effectType)
{
	if (_MID)
	{
		//test code
		_MID->SetVectorParameterValue(FName("da"), FLinearColor(1, 1, 1, 1));
	}
}

void UEffectControllerComponent::SetUpMaterialInsDynamic(int32 elementIndex)
{
	ACharacter* character = GetOwner<ACharacter>();
	if (!character) return;
	
	USkeletalMeshComponent* meshComp = character->GetMesh();
	if (!meshComp) return;

	UMaterialInterface* matInterface = meshComp->GetMaterial(elementIndex);
	if (!matInterface) return;

	_MID = UMaterialInstanceDynamic::Create(matInterface, this);

	meshComp->SetMaterial(elementIndex,_MID);
}


// Called every frame
void UEffectControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

