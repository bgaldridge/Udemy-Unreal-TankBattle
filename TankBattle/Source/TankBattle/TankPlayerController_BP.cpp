// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankPlayerController_BP.h"

void ATankPlayerController_BP::BeginPlay()
{
	Super::BeginPlay();

	//Check for controlled tank and log out
	ATank *PlayerTank = GetControlledTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player controlled tank not found!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controlled tank is %s"), *PlayerTank->GetName());
	}
	
}

//Find what tank the player (human or AI) is controlling
ATank* ATankPlayerController_BP::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

