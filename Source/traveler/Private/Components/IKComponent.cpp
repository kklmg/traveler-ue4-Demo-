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


}

void UIKComponent::FootTrace()
{
	if (!_meshSocketProvider) return;
	if (!_animationModelProvider) return;

	FTransform LeftFootTransform; 
    FTransform RightFootTransform;

    _meshSocketProvider->VTryGetMeshSocketTransform(EMeshSocketType::MST_LeftFoot,ERelativeTransformSpace::RTS_World,LeftFootTransform);
    _meshSocketProvider->VTryGetMeshSocketTransform(EMeshSocketType::MST_RightFoot,ERelativeTransformSpace::RTS_World,RightFootTransform);

    FVector traceStart;
    FVector traceEnd; 


	FHitResult pHitResult;
	TArray<AActor*> ignoreArray;
	ignoreArray.Add(GetOwner());

	bool bDebug = true;

	bool bResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(), traceStart, traceEnd,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, ignoreArray, EDrawDebugTrace::None, pHitResult, true);
}

