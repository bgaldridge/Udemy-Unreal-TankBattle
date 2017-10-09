// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	auto Name = GetOwner()->GetName();
	
	
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	float MaxTrackDrivingForce = MaxAcceleration * TankRoot->GetMass();
	FVector ForceApplied = GetForwardVector() * RelativeThrottle * MaxTrackDrivingForce;
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}

//void UTankTrack::Move(float RelativeSpeed)
//{
	//Clamp the relative speed to appropriate range
//	float ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	//Calc movement change this frame
//	auto MovementChangeThisFrame = ClampedRelativeSpeed * MaxMovementSpeed * GetWorld()->DeltaTimeSeconds;
	//Calc what new movement is this frame
//	auto NewMovement = RelativeLocation + MovementChangeThisFrame;
	//Set the new movement of the track
//	SetRelativeLocation(NewMovement);
//}


