// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/IKComponent.h"
#include "Interface/AnimationModelProvider.h"
#include "Interface/MeshSocketTransformProvider.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UIKComponent::UIKComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIKComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_animationModelProvider = GetOwner<IAnimationModelProvider>();
    _meshSocketProvider = GetOwner<IMeshSocketTransformProvider>();

}


// Called every frame
void UIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (_bActivateFootIK)
	{	// ...
		_IKDataLeftFoot = FootTrace(EMeshSocketType::MST_LeftFoot);
		_IKDataRightFoot = FootTrace(EMeshSocketType::MST_RightFoot);
	}
}

FIKData UIKComponent::FootTrace(EMeshSocketType meshSocketType)
{
	if (!_meshSocketProvider) return FIKData();
	if (!_animationModelProvider) return FIKData();

	FIKData result;

	//get Foot Transform
	FTransform out_FootTransform; 
    _meshSocketProvider->VTryGetMeshSocketTransform(meshSocketType,ERelativeTransformSpace::RTS_World, out_FootTransform);
	FVector footLocation = out_FootTransform.GetLocation();

	//get actor bounds
	FVector out_Origin;
	FVector out_Extent;
	GetOwner()->GetActorBounds(true, out_Origin, out_Extent);
	
	//Line Tracting parameters
	FVector actorLocation = GetOwner()->GetActorLocation();

	FVector TraceStart(footLocation.X, footLocation.Y, actorLocation.Z);
	FVector TraceEnd(footLocation.X, footLocation.Y, actorLocation.Z - out_Extent.Z-10.0f);
	
	FHitResult hitResult;
	TArray<AActor*> ignoreArray;
	ignoreArray.Add(GetOwner());

	//Execute Line Tracing 
	if(UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ignoreArray, EDrawDebugTrace::ForOneFrame, hitResult, true))
	{
		result.Offset = TraceStart.Z - hitResult.Distance;
		result.bImpact = true;
	}

	return result;
}

FIKData UIKComponent::GetIKData_LeftFoot()
{
	return _IKDataLeftFoot;
}

FIKData UIKComponent::GetIKData_RightFoot()
{
	return _IKDataRightFoot;
}

