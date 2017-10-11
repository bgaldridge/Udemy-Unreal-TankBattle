// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	//Get root component
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	
	//Add force to track, checking the max acceleration first
	auto ActorTank = Cast<ATank>(GetOwner());
	float MaxTrackDrivingForce = ActorTank->MaxAcceleration * TankRoot->GetMass();
	FVector ForceApplied = GetForwardVector() * RelativeThrottle * MaxTrackDrivingForce;
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}


