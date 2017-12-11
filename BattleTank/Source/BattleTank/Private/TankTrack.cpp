// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplyAntiSlippingForce()
{
	// ***** Fix sideways slipping *****
	// 1. Calculate the slippage speed.
	double slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	// 2. Work out the required acceleration this frame to correct.
	FVector correctionAcceleration = -((slippageSpeed / GetWorld()->GetDeltaSeconds()) * GetRightVector());
	// 3. Calculate and apply sideways friction force (F = ma)
	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * correctionAcceleration / 2.0f); // Div by 2 because we have 2 tracks.
	// 4. Apply force in the opposite direction of the slippage.
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0f, 1.0f);	
}

void UTankTrack::DriveTrack()
{
	FVector forceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormaliseImpulse,
	const FHitResult& Hit)
{
	DriveTrack();
	ApplyAntiSlippingForce();
	CurrentThrottle = 0.0f;
}