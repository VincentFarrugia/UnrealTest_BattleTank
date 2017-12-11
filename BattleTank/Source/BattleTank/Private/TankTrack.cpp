// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tank: '%s' has Throttle: '%f'"), *GetName(), Throttle);

	FVector forceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (TankRoot)
	{
		TankRoot->AddForceAtLocation(forceApplied, forceLocation);
	}
}
