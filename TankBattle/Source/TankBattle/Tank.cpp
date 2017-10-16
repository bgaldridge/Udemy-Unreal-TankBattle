// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector AimLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

//initialize tank barrel and turret
void ATank::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->Initialize(BarrelToSet, TurretToSet);
}


void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (ensure(Barrel) && isReloaded)
	{
		//spawn projectile actor
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileStart")),
			Barrel->GetSocketRotation(FName("ProjectileStart")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts
void ATank::BeginPlay()
{
	Super::BeginPlay();
}