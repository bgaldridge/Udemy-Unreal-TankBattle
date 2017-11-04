// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercentage() const
{
	return TankHealth/StartingHealth;
}

// Called when the game starts
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float DamageToApply = FMath::Clamp(DamageAmount, 0.f, TankHealth);

	TankHealth = TankHealth - DamageToApply;

	if (TankHealth <= 0)
	{
		OnDeath.Broadcast(); //Broadcast the event to all listeners when tank (AI or player) is dead
	}

	return DamageToApply;
}