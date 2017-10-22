// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

//Forward declaration
class UTankTrack;
/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void IntendRotate(float Throw);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxVelocity = 700; // cm/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxAcceleration = 1500; // cm/s^2

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxAngularVelocity = 35; // deg/s

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack *LeftTrack = nullptr; 
	UTankTrack *RightTrack = nullptr;


};
