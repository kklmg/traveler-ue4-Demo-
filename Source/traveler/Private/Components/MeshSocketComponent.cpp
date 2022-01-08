// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MeshSocketComponent.h"

// Sets default values for this component's properties
UMeshSocketComponent::UMeshSocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMeshSocketComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMeshSocketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//FName UMeshSocketComponent::GetMeshSocketNameByType(EMeshSocketType meshSocketType)
//{
//	if (_socketsMap.Contains(meshSocketType))
//	{
//		return _socketsMap[meshSocketType];
//	}
//	else
//	{
//		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMeshSocketType"), true);
//		if (EnumPtr)
//		{
//			FString enumName = EnumPtr->GetNameStringByIndex((int32)meshSocketType);
//			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Not registered MeshSocket: " + enumName));
//		}
//		return "";
//	}
//}
//
//bool UMeshSocketComponent::GetMeshSocketTransform(EMeshSocketType meshSocketType, ERelativeTransformSpace transformSpace, FTransform& outTransform)
//{
//
//		if (GetOwner() == nullptr)return;
//
//		if (_socketsMap.Contains(meshSocketType))
//		{
//			outTransform = GetMesh()->GetSocketTransform(_socketsMap[meshSocketType]);
//			return true;
//		}
//		else
//		{
//			const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMeshSocketType"), true);
//			if (EnumPtr)
//			{
//				FString enumName = EnumPtr->GetNameStringByIndex((int32)meshSocketType);
//				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Not registered MeshSocket: " + enumName));
//			}
//			return false;
//		}
//}
//