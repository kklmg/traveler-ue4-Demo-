// Fill out your copyright notice in the Description page of Project Settings.


#include "Simulator/SimulatorBase.h"

USimulatorBase::USimulatorBase()
{


}

void USimulatorBase::Tick(float deltaTime)
{
	_sectionProcessElapsedTime += deltaTime;
	_totalProcessElapsedTime += deltaTime;

	if (_processSections.Num() > curProcessIndex) return;

	

	if (_sectionProcessElapsedTime > _processSections[curProcessIndex].durationTime)
	{
		curProcessIndex++;
	
	}
	
}
