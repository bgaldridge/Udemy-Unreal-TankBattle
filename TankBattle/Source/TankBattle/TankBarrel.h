// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * StaticMesh used to control elevation barrel is aiming (pitch)
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max down move and +1 is up max speed
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 7;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinBarrelAngleDegrees = -10;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxBarrelAngleDegrees = 20;
};
