// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController_BP.generated.h" //Must be last include

/**
 * 
 */

//Forward declarations
class UTankAimingComponent;

UCLASS()
class TANKBATTLE_API ATankPlayerController_BP : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent *AimingComponentRef);

private:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair(); //Moves barrel towards where player is aiming

	bool GetSightRayHitLocation(FHitResult& OutHit) const; //Find if the sights hit the landscape and if it does, give coordinates

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int CannonRange = 1000000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float CrossHairYLocation = 0.33333f;

	UTankAimingComponent *AimingComponent;
};
