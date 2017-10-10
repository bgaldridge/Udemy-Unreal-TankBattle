// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"
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
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s with cross product Z value = %f"), *GetOwner()->GetName(), CrossProductBetween.Z)
	IntendRotate(CrossProductBetween.Z);

	//TODO fix friction issue(s)

	//UE_LOG(LogTemp, Warning, TEXT("Tank %s with MoveVelocity = %s"), *GetOwner()->GetName(), *MoveVelocity.GetSafeNormal().ToString())
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	
	//TODO place max speed
}

void UTankMovementComponent::IntendRotate(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

	//TODO place max rotate speed
}

