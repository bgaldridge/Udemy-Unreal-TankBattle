// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	auto Name = GetOwner()->GetName();
		
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	float MaxTrackDrivingForce = MaxAcceleration * TankRoot->GetMass();
	FVector ForceApplied = GetForwardVector() * RelativeThrottle * MaxTrackDrivingForce;
	//UE_LOG(LogTemp, Warning, TEXT("Force applied on tank name %s, track %s = %s"), *Name, *GetName(),*ForceApplied.ToString())
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}


