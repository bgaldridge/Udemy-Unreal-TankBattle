// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declaration
class UTankBarrel;

//Holds barrel aiming method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Gives aim location
	void AimAt(FVector AimLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void MoveBarrel(FVector LaunchDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//The barrel, which we will get from blueprint
	UTankBarrel* Barrel = nullptr;
};
