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
}

//Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ensure(PlayerTank))
	{
		//Move towards the player
		MoveToActor(PlayerTank, AIBufferRadius);
		
		//Aim at player and fire
		if (!ensure(AITank)) { return; }
		AITank->AimAt(PlayerTank->GetActorLocation());
		//AITank->Fire();
	}
}
