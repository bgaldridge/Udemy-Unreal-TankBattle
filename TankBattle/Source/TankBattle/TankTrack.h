// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

//Forward declarations
class UTankMovementComponent;

/**
 * StaticMesh that is used to set driving forces to tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float RelativeThrottle);
	//-1 is max reverse move and +1 is forward max speed
	//void Move(float RelativeSpeed);

	UTankMovementComponent *TankMovementComponent = nullptr;



private:
	UTankTrack();

	// Called when the game starts
	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle;
};
