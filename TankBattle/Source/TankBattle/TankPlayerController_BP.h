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
	
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;	

	void AimTowardsCrosshair(); //Moves barrel towards where player is aiming

	bool GetSightRayHitLocation(FVector& OutHitLocation) const; //Find if the sights hit the landscape and if it does, give coordinates

private:
	UPROPERTY(EditAnywhere)
	float CannonRange = 1000.f;

	FVector OutHitLocation; //Out parameter for hit location
	FVector PlayerLocation; //Out parameter for player view location
	FRotator PlayerCameraRotation;//Out parameter for player view rotation

};
