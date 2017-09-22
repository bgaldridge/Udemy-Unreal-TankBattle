// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankPlayerController_BP.h"

//Find what tank the player (human or AI) is controlling
ATank* ATankPlayerController_BP::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

