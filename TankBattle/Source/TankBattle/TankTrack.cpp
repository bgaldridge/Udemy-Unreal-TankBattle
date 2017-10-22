// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	//Get root component
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//Add force to track, checking the max acceleration first
	
	TankMovementComponent = GetOwner()->FindComponentByClass<UTankMovementComponent>();
	float MaxTrackDrivingForce =  TankMovementComponent->MaxAcceleration * TankRoot->GetMass();
	FVector ForceApplied = GetForwardVector() * RelativeThrottle * MaxTrackDrivingForce;
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}


