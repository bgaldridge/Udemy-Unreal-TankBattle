// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankAimingComponent; 
class UTankMovementComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector AimLocation);

	//Function that can be used in blueprint to find the end of barrel adn turret location
	//Uses TankAimingComponent
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);


	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire(); //fire a projectile

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxVelocity = 700; // cm/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxAcceleration = 1500; // cm/s^2

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxAngularVelocity = 35; // deg/s

protected:
	//reference to components on tank
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent* TankMovementComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;// Time to fire again

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO remove

	double LastFireTime = 0; //previous fire time
};
