// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void UTankTurret::Turn(float i_relativeSpeedInDegPerSecond)
{
	float clampedRelativeSpeed = FMath::Clamp(i_relativeSpeedInDegPerSecond, -1.0f, 1.0f);
	float yawChange = clampedRelativeSpeed * MaxTurnSpeedInDegPerSecond * GetWorld()->DeltaTimeSeconds;
	float rawNewYaw = RelativeRotation.Yaw + yawChange;
	//float clampedYaw = FMath::Clamp(rawNewYaw, MinTurnYawDegrees, MaxTurnYawDegrees);	
	SetRelativeRotation(FRotator(0.0f, rawNewYaw, 0.0f));
}