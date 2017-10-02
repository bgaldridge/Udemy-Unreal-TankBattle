// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//Find AITank (self) and Player Tank
	AITank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	//Log error if no AITank or PlayerTank
	if (!AITank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI controlled tank not found on TankAIController!!"));
	}

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player controlled tank not found from TankAIController!!"));
	}
}

//Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerTank)
	{
		//Aim at player and fire
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Fire();
	}
}
