// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->SetAutoActivate(false);//Do no auto activate the projectile (activation is done later)
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire projectile!"));
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);//Set projectile velocity vector
	ProjectileMovementComponent->Activate(); //activate projectile
}
