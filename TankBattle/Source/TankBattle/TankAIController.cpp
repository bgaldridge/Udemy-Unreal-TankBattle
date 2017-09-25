// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//Check for controlled tank and log out
	ATank *AITank = GetAIControlledTank();
	if (!AITank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI controlled tank not found!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controlled tank is %s"), *AITank->GetName());
	}

	//What is the player controlled tank
	ATank *PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player tank controlled tank not found!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controlled tank is %s"), *PlayerTank->GetName());
	}

}

//Find what tank the AI is controlling
ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//Find what the player tank is
ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
