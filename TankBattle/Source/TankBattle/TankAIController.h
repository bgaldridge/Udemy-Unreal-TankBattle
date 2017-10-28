// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

//Forward delcations
class UTankAimingComponent;


/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	APawn *ControlledTank;
	APawn *PlayerTank;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//How close can AI tank get to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AIBufferRadius = 8000;
	
};