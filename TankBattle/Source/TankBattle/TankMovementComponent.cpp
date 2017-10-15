// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"
#include "Tank.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No super, replacing functionality
	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal(); //direction tank is facing
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal(); //Get the direction that the tank wants to move (after pathfinding)
	
	float DotProductBetween = FVector::DotProduct(AIForwardIntention, TankForwardDirection);
	FVector CrossProductBetween = FVector::CrossProduct(TankForwardDirection, AIForwardIntention);

	IntendMoveForward(DotProductBetween);
	IntendRotate(CrossProductBetween.Z);

	//TODO fix friction issue(s)

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	
	//If current velocity is greater than max, do not add more force
	if ((Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetComponentVelocity().Size()) > Cast<ATank>(GetOwner())->MaxVelocity){return;}
	//else continue acceleration
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotate(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	//If current angular velocity is greater than max, do not acelerate rotation
	if ((Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent())->GetPhysicsAngularVelocity().Size()) > Cast<ATank>(GetOwner())->MaxAngularVelocity) { return; }
	//else, rontinue rotation acceleration
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

