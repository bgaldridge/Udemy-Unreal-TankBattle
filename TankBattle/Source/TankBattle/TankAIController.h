// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

//Forward delcations
class UTankAimingComponent;
class ATank;

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	APawn *ControlledTank;
	ATank *PlayerTank;
	bool PlayerTankDead = false;

	virtual void SetPawn(APawn *InPawn) override; //Called when pawn is possesed

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//How close can AI tank get to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AIBufferRadius = 8000;

	UFUNCTION()
		void OnPossedTankDeath(); //function to be called when delegate on Tank broadcasts death

	UFUNCTION()
		void OnPlayerTankDeath();//Called when delegate on player tank broadcasts death
	
};