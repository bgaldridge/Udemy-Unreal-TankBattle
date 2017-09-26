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

private:
	ATank* GetControlledTank() const; //What tank is the player controlling
	
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;	

	void AimTowardsCrosshair(); //Moves barrel towards where player is aiming

	bool GetSightRayHitLocation(FHitResult& OutHit) const; //Find if the sights hit the landscape and if it does, give coordinates

	UPROPERTY(EditAnywhere)
		int CannonRange = 1000000;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.33333f;



};
