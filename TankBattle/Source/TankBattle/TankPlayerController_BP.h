// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController_BP.generated.h" //Must be last include

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController_BP : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const; //What tank is the player controlling
	
	
};
