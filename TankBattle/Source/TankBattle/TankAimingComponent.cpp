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
	PrimaryComponentTick.bCanEverTick = true;

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
	
	if (AmmoCounter == 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
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

//***************************************************
//Move the turrent based on the direction the aiming retical is looking at and the current direction the barrel is facing
//***************************************************
void UTankAimingComponent::MoveTurret(FVector LaunchDirection)
{
	//Note: ptr protection in AimAt
	//Get delta of rotation needed
	float DeltaRotator = LaunchDirection.Rotation().Yaw - Turret->GetForwardVector().Rotation().Yaw;

	//Pick DeltaRotator so that rotation is always in closest and correct direction
	if (DeltaRotator > 180)
	{
		DeltaRotator = -DeltaRotator;
	}
	 //UE_LOG(LogTemp, Warning, TEXT("Delta Rotator on Tank %s = %f"),*Turret->GetOwner()->GetName(), DeltaRotator)
	//TODO: Fix rotation issue about x-axis (becomes -360)
	Turret->Rotate(DeltaRotator);

}

//***************************************************
//Come up with 
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
	if ((FiringStatus != EFiringStatus::Reloading)&&(FiringStatus != EFiringStatus::OutOfAmmo))
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		//spawn projectile actor
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileStart")),
			Barrel->GetSocketRotation(FName("ProjectileStart")));

		Projectile->LaunchProjectile(LaunchSpeed);
		AmmoCounter = AmmoCounter - 1;
		LastFireTime = FPlatformTime::Seconds();
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetAmmoCount() const
{
	return AmmoCounter;
}

