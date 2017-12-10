// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void UTankBarrel::Elevate(float i_relativeSpeedInDegPerSecond)
{
	float clampedRelativeSpeed = FMath::Clamp(i_relativeSpeedInDegPerSecond, -1.0f, 1.0f);
	float elevationChange = clampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float clampedNewElevation = FMath::Clamp(rawNewElevation, MinElevationInDegrees, MaxElevationInDegrees);
	SetRelativeRotation(FRotator(clampedNewElevation, 0, 0));
}