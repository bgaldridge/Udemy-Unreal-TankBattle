// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{

	//Clamp the relative speed to appropriate range
	float ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	//Calc rotation change this frame
	auto RotationChangeThisFrame = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	//Calc what new rotation is this frame
	auto NewRotation = RelativeRotation.Yaw + RotationChangeThisFrame;
	//Set the new rotation of the turret
	SetRelativeRotation(FRotator(0, NewRotation, 0));

}


