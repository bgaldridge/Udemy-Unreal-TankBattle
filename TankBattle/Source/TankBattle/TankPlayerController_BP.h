// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController_BP.generated.h" //Must be last include

/**
 * 
 */

//Forward declarations
class ATank;

UCLASS()
class TANKBATTLE_API ATankPlayerController_BP : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const; //What tank is the player controlling
	
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;	

	void AimTowardsCrosshair(); //Moves barrel towards where player is aiming

	bool GetSightRayHitLocation(FHitResult& OutHit) const; //Find if the sights hit the landscape and if it does, give coordinates

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		int CannonRange = 1000000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float CrossHairYLocation = 0.33333f;

};
