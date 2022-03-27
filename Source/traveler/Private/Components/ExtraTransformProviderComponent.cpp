// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ExtraTransformProviderComponent.h"
#include "GameSystem/DebugMessageHelper.h"

// Sets default values for this component's properties
UExtraTransformProviderComponent::UExtraTransformProviderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UExtraTransformProviderComponent::Initialize(USkeletalMeshComponent* skeletalMeshComp)
{
	_skeletalMeshComp = skeletalMeshComp;
}

// Called when the game starts
void UExtraTransformProviderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UExtraTransformProviderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UExtraTransformProviderComponent::VTryGetSocketName(ETransform transformType, FName& outSocketName)
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

bool UExtraTransformProviderComponent::TryGetTransform(ETransform transformType, ERelativeTransformSpace transformSpace, FTransform& outTransform)
{
	//try get bone Transform
	if (_skeletalMeshComp && _boneNameMap.Contains(transformType))
	{
		outTransform = _skeletalMeshComp->GetSocketTransform(_boneNameMap[transformType], transformSpace);
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

