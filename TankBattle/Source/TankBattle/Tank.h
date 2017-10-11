// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TankAimingComponent.h"
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
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);//given barrel from blueprint

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);//given turret from blueprint

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire(); //fire a projectile

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxVelocity = 700; // cm/s

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxAcceleration = 1500; // cm/s^2

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxAngularVelocity = 35; // deg/s

protected:
	//default components on Tank
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;


private:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr; //local barrel reference for spawning projectile

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;// Time to fire again

	double LastFireTime = 0; //previous fire time
};
