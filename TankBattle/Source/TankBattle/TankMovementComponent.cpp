// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"
#include "Tank.h"
#include "TankMovementComponent.h"
//Has input from blueprint
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

	//ptr protection in functions
	IntendMoveForward(DotProductBetween);
	IntendRotate(CrossProductBetween.Z);

	//TODO fix friction issue(s)

	//TODO fix bumps when driving

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	//TODO: Check if limitation on speed and/or roation is still needed
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotate(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	//Note: Angular Dampening is applied!
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

