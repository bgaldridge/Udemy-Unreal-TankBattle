// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
//Depends on movement component via pathfinding
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
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
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Loaded) //Fire if locked
		{
			AimingComponent->Fire();
		}
	}
}
