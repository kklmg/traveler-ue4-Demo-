// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ExTransformProviderComponent.h"
#include "GameSystem/DebugMessageHelper.h"

// Sets default values for this component's properties
UExTransformProviderComponent::UExTransformProviderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UExTransformProviderComponent::Initialize(UMeshComponent* meshComp)
{
	_meshComp = meshComp;
}

// Called when the game starts
void UExTransformProviderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UExTransformProviderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UExTransformProviderComponent::TryGetSocketName(ETransform transformType, FName& outSocketName)
{
	if (_boneNameMap.Contains(transformType))
	{
		outSocketName = _boneNameMap[transformType];
		return true;
	}
	else
	{
		return false;
	}
}

bool UExTransformProviderComponent::TryGetTransform(ETransform transformType, ERelativeTransformSpace transformSpace, FTransform& outTransform)
{
	//try get bone Transform
	if (_meshComp && _boneNameMap.Contains(transformType))
	{
		outTransform = _meshComp->GetSocketTransform(_boneNameMap[transformType], transformSpace);
		return true;
	}

	//try get relative Transform
	else if(_relativeTransfromMap.Contains(transformType))
	{
		outTransform = _relativeTransfromMap[transformType] * GetOwner()->GetActorTransform();

		return true;
	}

	else
	{
		UDebugMessageHelper::Messsage_Enum(TEXT("No Transform Data"), TEXT("ETransform"), (int32)transformType);
		return false;
	}
}

