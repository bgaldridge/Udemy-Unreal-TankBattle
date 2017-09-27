// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Clamp the relative speed to appropriate range
	float ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	//Calc elevation change this frame
	auto ElevationChangeThisFrame = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	//Calc what new elevation is this frame
	auto NewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChangeThisFrame, MinBarrelAngleDegrees, MaxBarrelAngleDegrees);
	//Set the new rotation of the barrel
	SetRelativeRotation(FRotator(NewElevation, 0, 0));

	
	//UE_LOG(LogTemp, Warning, TEXT("%f: Elevate called on %s"), GetWorld()->GetRealTimeSeconds(), *GetOwner()->GetName())
}


