// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"
#include "Status/BasicStatus.h"
#include "Data/CostData.h"
#include "Data/AnimationModelBase.h"
#include "Components/AnimControlComponent.h"
#include "Status/StatusTableRow.h"
#include "Status/LevelStatus.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bWantsInitializeComponent = true;
	_defaultLevel = 1;
}


void UStatusComponent::InitializeComponent()
{
	UAnimControlComponent* animControlComp = Cast<UAnimControlComponent>(GetOwner()->GetComponentByClass(UAnimControlComponent::StaticClass()));
	if (animControlComp)
	{
		_animationViewModel = animControlComp->GetAnimationModel();
	}

	InitializeStatusData();
}

// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (auto basicStatus : _basicStatusMap)
	{
		basicStatus.Value->Tick(DeltaTime);
	}
}

UStatusBase* UStatusComponent::GetStatusIns(EStatusType statusType)
{
	if (_statusMap.Contains(statusType))
	{
		return _statusMap[statusType];
	}
	else if (_basicStatusMap.Contains(statusType))
	{
		return _statusMap[statusType];
	}
	else
	{
		return nullptr;
	}
}

UBasicStatus* UStatusComponent::GetBasicStatusIns(EStatusType statusType)
{
	return _basicStatusMap.Contains(statusType) ? _basicStatusMap[statusType] : nullptr;
}

int32 UStatusComponent::GetLevelValue()
{
	return _levelStatusIns->GetLevel();
}

ULevelStatus* UStatusComponent::GetLevelStatusIns()
{
	return _levelStatusIns;
}

float UStatusComponent::GetPrimaryValue(EStatusType statusType)
{
	UStatusBase* statusBaseIns = GetStatusIns(statusType);
	return statusBaseIns ? statusBaseIns->GetPrimaryValue() : 0.0f;
}

float UStatusComponent::GetBasicValue(EStatusType statusType)
{
	UStatusBase* statusBaseIns = GetStatusIns(statusType);
	return statusBaseIns ? statusBaseIns->GetBasicValue() : 0.0f;
}

float UStatusComponent::GetFinalValue(EStatusType statusType)
{
	UStatusBase* statusBaseIns = GetStatusIns(statusType);
	return statusBaseIns ? statusBaseIns->GetFinalValue() : 0.0f;
}

float UStatusComponent::GetRemainingValue(EStatusType statusType)
{
	return _basicStatusMap.Contains(statusType) ? _basicStatusMap[statusType]->GetRemainingValue() : 0.0f;
}

void UStatusComponent::ApplyRemainingValueChange(EStatusType statusType, float value)
{
	if (_basicStatusMap.Contains(statusType))
	{
		_basicStatusMap[statusType]->ApplyValueChange(value);
	}
}

bool UStatusComponent::IsRemainingValueEnough(UCostData* costData)
{
	if (!costData) return true;

	auto costArray = costData->GetCostArray();
	for (auto costPair : costArray)
	{
		if (GetRemainingValue(costPair.Key) < costPair.Value)
		{
			return false;
		}
	}
	return true;
}

bool UStatusComponent::ApplyCost(UCostData* costData)
{
	if (!costData) return true;
	if (!IsRemainingValueEnough(costData)) return false;

	auto costArray = costData->GetCostArray();
	for (auto costPair : costArray)
	{
		ApplyRemainingValueChange(costPair.Key, - costPair.Value);
	}
	return true;
}

void UStatusComponent::InitializeStatusData()
{

	//Initialize level status
	_levelStatusIns = NewObject<ULevelStatus>(this);
	_levelStatusIns->SetLevel(_defaultLevel);

	//Initialize status
	if (_statusTable)
	{
		FString contextString;
		TArray<FStatusTableRow*> rows;

		//get all rows from table
		_statusTable->GetAllRows<FStatusTableRow>(contextString, rows);

		for (FStatusTableRow* row : rows)
		{
			if (!row) continue;

			//basic status
			if (row->IsBasicStatus())
			{
				if (_basicStatusMap.Contains(row->StatusType))
				{
					UE_LOG(LogTemp, Warning, TEXT("Duplicated status Data in Table"))
				}
				else
				{
					UBasicStatus* newBasicStatus = NewObject<UBasicStatus>(this);
					newBasicStatus->VInitialize(*row, _levelStatusIns->GetLevel());

					_basicStatusMap.Add(row->StatusType,newBasicStatus);
					_statusMap.Add(row->StatusType,newBasicStatus);
				}
			}
			//normal status
			else
			{
				if (_statusMap.Contains(row->StatusType))
				{
					UE_LOG(LogTemp, Warning, TEXT("Duplicated status Data in Table"))
				}
				else
				{
					UStatusBase* newStatus = NewObject<UStatusBase>(this);
					newStatus->VInitialize(*row, _levelStatusIns->GetLevel());

					_statusMap.Add(row->StatusType, newStatus);
				}
			}
		}
	}

	if (_animationViewModel)
	{
		if (_statusMap.Contains(EStatusType::EStatus_WalkingSpeed))
		{
			_animationViewModel->SetFloat(NSAnimationDataKey::fWalkingSpeed, _statusMap[EStatusType::EStatus_WalkingSpeed]->GetFinalValue());
		}

		if (_statusMap.Contains(EStatusType::EStatus_SprintingSpeed))
		{
			_animationViewModel->SetFloat(NSAnimationDataKey::fSprintingSpeed, _statusMap[EStatusType::EStatus_SprintingSpeed]->GetFinalValue());
		}
	}
}




//void UAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME(UAttributeComponent, _health);
//	DOREPLIFETIME(UAttributeComponent, _mana);
//	DOREPLIFETIME(UAttributeComponent, _energy);
//}

