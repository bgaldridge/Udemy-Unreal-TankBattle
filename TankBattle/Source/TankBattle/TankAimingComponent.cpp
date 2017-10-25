// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//Set so that first file is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (!IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Loaded;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	return FMath::IsNearlyEqual(OutLaunchVelocity.Rotation().Yaw, Turret->GetForwardVector().Rotation().Yaw, 0.1f);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector LaunchDirection)
{
	//Note: ptr protection in AimAt
	//Get current barrel coordinates
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator LaunchRotation = LaunchDirection.Rotation();
	FRotator DeltaRotator = LaunchRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurret(FVector LaunchDirection)
{
	//Note: ptr protection in AimAt
	//Get current barrel coordinates
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator LaunchRotation = LaunchDirection.Rotation();
	float DeltaRotator;
	//Pick DeltaRotator so that rotation is always in closest and correct direction
	if ((TurretRotation.Yaw < 0) && (LaunchRotation.Yaw > 0)) //TODO Fix so that it works in all directions
	{
		DeltaRotator = TurretRotation.Yaw - LaunchRotation.Yaw;
	}
	else
	{
		DeltaRotator = LaunchRotation.Yaw - TurretRotation.Yaw;
	}
	 
	Turret->Rotate(DeltaRotator);

}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel && Turret)) { return; }
	
		FVector BarrelHeadLocation = Barrel->GetSocketLocation(FName("ProjectileStart")); //Start location of projectile

	//Calculate the OutLaunchVelocity
	
	if (UGameplayStatics::SuggestProjectileVelocity(this, 
		OutLaunchVelocity, 
		BarrelHeadLocation, 
		AimLocation, 
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace)) //last line must be present to prevent bug
	{
		FVector LaunchDirection = OutLaunchVelocity.GetSafeNormal(); //Makes unit vector in direction of launchvelcotiy
		
		//Move the barrel and turret based on the calculated launch direction
		MoveBarrel(LaunchDirection);
		MoveTurret(LaunchDirection);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//spawn projectile actor
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileStart")),
			Barrel->GetSocketRotation(FName("ProjectileStart")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}