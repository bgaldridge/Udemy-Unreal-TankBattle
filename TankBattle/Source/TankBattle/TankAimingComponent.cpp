// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::MoveBarrel(FVector LaunchDirection)
{
	//Get current barrel coordinates
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator LaunchRotation = LaunchDirection.Rotation();
	FRotator DeltaRotator = LaunchRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurret(FVector LaunchDirection)
{
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
	 
	//if (GetOwner()->GetName() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetName())
	//{
	//	float LaunchRotationReport = LaunchRotation.Yaw;
	//	float TurretRotationReport = TurretRotation.Yaw;

	//	UE_LOG(LogTemp, Warning, TEXT("Delta rotator = %f-%f=%f"), LaunchRotationReport, TurretRotationReport, DeltaRotator)
	//}
	Turret->Rotate(DeltaRotator);

}

void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
	
	if ((!Barrel)||(!Turret))
	{		
		return;
	}
	
	FVector OutLaunchVelocity;
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
		//auto TankName = GetOwner()->GetName();
		
		//Move the barrel and turret based on the calculated launch direction
		MoveBarrel(LaunchDirection);
		MoveTurret(LaunchDirection);
	}
	else
	{

	}
}

