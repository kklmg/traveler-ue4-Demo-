// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Bow.h"

void ABow::Fire() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Trigger Fire");


}

void ABow::OnFireEnd() 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Fire Finished");
}