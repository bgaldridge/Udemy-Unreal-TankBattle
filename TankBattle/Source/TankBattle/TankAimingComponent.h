// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enums for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Loaded,
	OutOfAmmo
};

//Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Holds barrel aiming method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Gives aim location
	void AimAt(FVector AimLocation);

	//Initialize barrel and turrent
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//Move barrel and turret
	void MoveBarrel(FVector LaunchDirection);
	void MoveTurret(FVector LaunchDirection);

	//Fire a projectile
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BLueprintCallable, Category = "Firing")
	int GetAmmoCount() const;

protected:
	//Firing status enum
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int StartingAmmo = 10;
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
		int AmmoCounter = StartingAmmo;

	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//The barrel and turret, which we will get from blueprint
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector OutLaunchVelocity;

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;// Time to fire again

	double LastFireTime = 0; //previous fire time

};
