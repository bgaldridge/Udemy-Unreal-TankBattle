// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);//Used to register hit event
}


void UTankTrack::ApplySidewaysForce()
{
	//*************************************
	//Apply sideways force to counteract slipping (since tank is sitting on top of environment)
	//*************************************
	//Calculate slippage speed
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//Calc required acceleration this frame to correct
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectiongAcceleration = -SlippageSpeed / DeltaTime *GetRightVector();

	//Calculate and apply sideways force
	UStaticMeshComponent *TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * CorrectiongAcceleration / 2; //Divide by two since two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float RelativeThrottle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + RelativeThrottle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//Get root component
	UStaticMeshComponent *TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	//Add force to track, checking the max acceleration first

	TankMovementComponent = GetOwner()->FindComponentByClass<UTankMovementComponent>();
	float MaxTrackDrivingForce = TankMovementComponent->MaxAcceleration * TankRoot->GetMass();
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * MaxTrackDrivingForce;
	TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack(); //Apply force to move tank (via tracks)

	ApplySidewaysForce(); //Apply force to stop slippage

	CurrentThrottle = 0;//Without this reset, throttle will stay at last value, even if no throttle is given
}

