// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankPlayerController_BP.h"

void ATankPlayerController_BP::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair(); //Update direction cannon/turret is aisming based on player 

}

//Find what tank the player (human or AI) is controlling
ATank* ATankPlayerController_BP::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//Move turret/cannon towards point player is aiming at
void ATankPlayerController_BP::AimTowardsCrosshair()
{
	if (!GetControlledTank()){return;}
	
	FHitResult OutHit;; //Out parameter for hit location

	//Get world location of crosshair through line trace and move cannon
	if (GetSightRayHitLocation(OutHit))
	{
		GetControlledTank()->AimAt(OutHit.Location);//Tank aims at specified location
	}
	
}

//Find if the sights hit the landscape and if it does, give coordinates
bool ATankPlayerController_BP::GetSightRayHitLocation(FHitResult &OutHit) const
{
	
	//Find the crosshair position
	int32 OutViewportSizeX, OutViewportSizeY;
	GetViewportSize(OutViewportSizeX, OutViewportSizeY);
	FVector2D ScreenLocation = FVector2D(OutViewportSizeX*CrossHairXLocation, OutViewportSizeY*CrossHairYLocation);

	//"de-project" the screen position of the crosshair to a world direction
	FVector OutCameraWorldLocation, OutCameraWorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutCameraWorldLocation, OutCameraWorldDirection))//returns unit vector of direction the camera is facing
	{
		//Line-trace along look direction and see what we hit up to max range		
		if (GetWorld()->LineTraceSingleByChannel(OutHit,
			OutCameraWorldLocation,
			OutCameraWorldLocation + OutCameraWorldDirection*CannonRange,
			ECC_Visibility,
			FCollisionQueryParams(FName(TEXT("")), false, GetOwner()),
			FCollisionResponseParams()))
		{
			return true; //if hit result is successfull
		}
		else
		{
			OutHit.Init(); //provide initialized to zero aiming
		}
	}
	
	return false; //if either screen location of hit fails, return false
}