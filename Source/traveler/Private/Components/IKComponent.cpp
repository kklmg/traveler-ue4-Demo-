// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/IKComponent.h"
#include "Components/AnimControlComponent.h"
#include "Components/ExTransformProviderComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Data/AnimationModelBase.h"

// Sets default values for this component's properties
UIKComponent::UIKComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	_traceOffset = 100.0f;
}


// Called when the game starts
void UIKComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_character = GetOwner<ACharacter>();
	if (_character)
	{
		_halfHeight = _character->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	}

	_exTransformProviderComp =
		Cast<UExTransformProviderComponent>(GetOwner()->GetComponentByClass(UExTransformProviderComponent::StaticClass()));

	UAnimControlComponent* animControlComp = 
		Cast<UAnimControlComponent>(GetOwner()->GetComponentByClass(UAnimControlComponent::StaticClass()));
	if(animControlComp)
	{
		_animationViewModel = animControlComp->GetAnimViewModel();
	}

	_footIKData = NewObject<UIKFootData>(this);
}


// Called every frame
void UIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// update foot ik data
	if (_bActivateFootIK && _character && _animationViewModel)
	{
		EMovementMode movementMode = _character->GetCharacterMovement()->MovementMode;

		if ((movementMode == EMovementMode::MOVE_Walking || movementMode == EMovementMode::MOVE_NavWalking))
		{ 
			//calculate ik data
			_footIKData->SetLeft(FootTrace(ETransformType::ETransform_LeftFoot));
			_footIKData->SetRight(FootTrace(ETransformType::ETransform_RightFoot));

			//notify ik data
			_animationViewModel->SetUObject(NSAnimationDataKey::objFootIKData, _footIKData);
		}
	}
}

FIKData UIKComponent::FootTrace(ETransformType meshSocketType)
{
	if (!_exTransformProviderComp) return FIKData();
	if (!_animationViewModel) return FIKData();

	FIKData result;

	//get Foot Transform
	FTransform out_FootTransform; 
	_exTransformProviderComp->TryGetTransform(meshSocketType,ERelativeTransformSpace::RTS_World, out_FootTransform);
	FVector footLocation = out_FootTransform.GetLocation();
	
	//Line Tracting parameters
	FVector actorLocation = GetOwner()->GetActorLocation();
	float groundHeight = actorLocation.Z - _halfHeight;

	FVector TraceStart(footLocation.X, footLocation.Y, actorLocation.Z);
	FVector TraceEnd(footLocation.X, footLocation.Y, groundHeight - _traceOffset);
	

	//DrawDebugLine(GetWorld(), curLocation, destLocXY, FColor::Green, false, -1.0f, 0U, 30.0f);
	///GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "origin: " + out_Origin.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "extent: " + out_Extent.ToString());

	FHitResult hitResult;
	TArray<AActor*> ignoreArray;
	ignoreArray.Add(GetOwner());

	//Execute Line Tracing 
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd, 
		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), true, ignoreArray, EDrawDebugTrace::None, hitResult, true))
	{
		result.Offset = hitResult.ImpactPoint.Z - groundHeight;
		result.bImpact = true;
		result.Normal = hitResult.Normal;

		
		float pitch = -FMath::RadiansToDegrees(FMath::Atan2(hitResult.Normal.X, hitResult.Normal.Z));
		float roll = FMath::RadiansToDegrees(FMath::Atan2(hitResult.Normal.Y,hitResult.Normal.Z));

		result.rotator = FRotator(pitch, 0.0f, roll);

		//DrawDebugLine(GetWorld(), hitResult.ImpactPoint, hitResult.ImpactPoint + result.Normal * 100, FColor::Black, false, -1.0f, 0U, 5.0f);
		//DrawDebugSphere(GetWorld(), hitResult.ImpactPoint,20,4,FColor::Purple);
		//DrawDebugBox(GetWorld(), out_Origin, out_Extent, FColor::Cyan);
	}

	return result;
}

