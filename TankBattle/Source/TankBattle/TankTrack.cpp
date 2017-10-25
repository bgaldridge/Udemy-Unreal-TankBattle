// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//*************************************
	//Apply sideways force to counteract slipping (since tank is sitting on top of environment)
	//*************************************
	//Calculate slippage speed
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//Calc required acceleration this frame to correct
	FVector CorrectiongAcceleration = -SlippageSpeed / DeltaTime *GetRightVector();

	//Calculate and apply sideways force
	UStaticMeshComponent *TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * CorrectiongAcceleration/2; //Divide by two since two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	//Get root component
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	//Add force to track, checking the max acceleration first
	
	TankMovementComponent = GetOwner()->FindComponentByClass<UTankMovementComponent>();
	float MaxTrackDrivingForce =  TankMovementComponent->MaxAcceleration * TankRoot->GetMass();
	FVector ForceApplied = GetForwardVector() * RelativeThrottle * MaxTrackDrivingForce;
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}


