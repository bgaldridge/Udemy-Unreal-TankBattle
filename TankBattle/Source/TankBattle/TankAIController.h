// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	ATank* GetAIControlledTank() const; //What tank is the AI controlling

	void BeginPlay() override;
	
	ATank* GetPlayerTank() const; //returns pointer to player tank
};
