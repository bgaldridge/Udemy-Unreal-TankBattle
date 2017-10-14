// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TankAimingComponent.h"
//#include "Tank.h"
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

	ATank *AITank;
	ATank *PlayerTank;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//How close can AI tank get to player
	float AIBufferRadius = 300;
	
};
