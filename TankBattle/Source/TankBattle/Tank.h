// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Declare our delegate type
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	//Returns current health as a decimal percentage of starting health
	UFUNCTION(BlueprintPure, Category = "Status")
		float GetHealthPercentage() const;

	FTankDelegate OnDeath; //Create our delegate object which can be called in .cpp file

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Status")
		float TankHealth = StartingHealth;

};
