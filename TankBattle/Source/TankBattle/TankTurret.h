// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * StaticMesh used to control direction barrel is aiming (yaw)
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max down move and +1 is up max speed
	void Rotate(float RelativeSpeed);

private:

		float MaxDegreesPerSecond = 15;
	
	
};
