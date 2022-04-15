// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LifeControlComponent.h"
#include "Condition/CompositeActorCondition.h"
#include "Interface/AnimControlInterface.h"
#include "Interface/ActorEffectInterface.h"


// Sets default values for this component's properties
ULifeControlComponent::ULifeControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;
}


void ULifeControlComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called when the game starts
void ULifeControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	_lifeConditionIns = _lifeConditionClass ?
		NewObject<UCompositeActorCondition>(this, _lifeConditionClass) : NewObject<UCompositeActorCondition>(this);
	_lifeConditionIns->SetActor(GetOwner());
	_lifeConditionIns->Initialize();

	_actorEffectInterface = GetOwner<IActorEffectInterface>();


	if(_lifeConditionIns)
	{
		_lifeConditionIns->OnValidated.AddUObject(this, &ULifeControlComponent::OnLifeStateChanged);
	}

	IAnimControlInterface* animControlInterface = GetOwner<IAnimControlInterface>();
	if (animControlInterface)
	{
		_animViewModel = animControlInterface->VGetAnimationModel();
	}
	if (_animViewModel && _lifeConditionIns)
	{
		_animViewModel->SetBool(NSAnimationDataKey::bIsAlive, _lifeConditionIns->GetResult());
	}
}

void ULifeControlComponent::OnLifeStateChanged(bool isAlive)
{
	if(_animViewModel)
	{
		_animViewModel->SetBool(NSAnimationDataKey::bIsAlive,isAlive);
	}

	if (_actorEffectInterface) 
	{
		if(isAlive)
		{
			_actorEffectInterface->VStopEffect(EEffectType::EEffectType_Dissolve, 0);
		}
		else
		{
			_actorEffectInterface->VPlayEffect(EEffectType::EEffectType_Dissolve, 0);
		}

	}
}


// Called every frame
void ULifeControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULifeControlComponent::IsAlive()
{
	return _lifeConditionIns ? _lifeConditionIns->GetResult() : true;
}

FMD_BoolValueChangeSignature* ULifeControlComponent::GetLifeChangedDelegate()
{
	return _lifeConditionIns ? &_lifeConditionIns->OnValidated : nullptr;
}

