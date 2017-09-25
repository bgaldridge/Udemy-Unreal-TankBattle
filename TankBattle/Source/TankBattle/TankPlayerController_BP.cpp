// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankPlayerController_BP.h"

void ATankPlayerController_BP::BeginPlay()
{
	Super::BeginPlay();

	//Check for controlled tank and log out
	ATank *PlayerTank = GetControlledTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Your tank is not found!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Your tank is %s"), *PlayerTank->GetName());
	}
	
}

void ATankPlayerController_BP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair(); //Update direction cannon/turret is aisming based on player 

	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking..."));
}

//Find what tank the player (human or AI) is controlling
ATank* ATankPlayerController_BP::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//Move turret/cannon towards point player is aiming at
void ATankPlayerController_BP::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *OutHitLocation.ToString());

	//Get world location of crosshair through line trace and move cannon
	GetSightRayHitLocation(OutHitLocation);
}

//Find if the sights hit the landscape and if it does, give coordinates
bool ATankPlayerController_BP::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the player controlled pawn (or tank in this case)
	//ATank *PlayerTank = GetControlledTank();

	//Get player location and viewpoint
	//PlayerLocation = PlayerTank->GetActorLocation();
	//PlayerTank->CalcCamera(GetWorld()->GetTimeSeconds(), FMinimalViewInfo());

	//Find the location of the player view at the cannon range
	//FVector LineTraceEnd = PlayerLocation + PlayerCameraRotation.Vector()*CannonRange;

	//Do line trace and see if anything is hit
	//auto LineTraceParams = FCollisionQueryParams();
	//bool hit = PlayerTank->ActorLineTraceSingle(OutHitLocation, PlayerLocation, LineTraceEnd, ECC_WorldStatic, LineTraceParams);

	//Return hit status
	//return hit;
	OutHitLocation = FVector(1.0);

	return false;
}