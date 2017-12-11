// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ***** Fix sideways slipping *****
	// 1. Calculate the slippage speed.
	double slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// 2. Work out the required acceleration this frame to correct.
	FVector correctionAcceleration = -((slippageSpeed / DeltaTime) * GetRightVector());
	// 3. Calculate and apply sideways friction force (F = ma)
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration / 2.0f); // Div by 2 because we have 2 tracks.
	// 4. Apply force in the opposite direction of the slippage.
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	FVector forceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (TankRoot)
	{
		TankRoot->AddForceAtLocation(forceApplied, forceLocation);
	}
}