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
	Loaded
};

//Forward declaration
class UTankBarrel;
class UTankTurret;

//Holds barrel aiming method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Gives aim location
	void AimAt(FVector AimLocation, float LaunchSpeed);

	//Initialize barrel and turrent
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//Move barrel and turret
	void MoveBarrel(FVector LaunchDirection);
	void MoveTurret(FVector LaunchDirection);

protected:
	//Firing status enum
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Aiming;

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



};
