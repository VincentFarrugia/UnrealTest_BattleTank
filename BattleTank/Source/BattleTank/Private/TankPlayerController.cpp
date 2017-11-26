// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrintOutPossessedTankName();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{	
	if (!GetControlledTank()) { return; }

	// Raycast crosshair to get the world location.

	// If the raycast hits the landscape:

	// Call Aim on the Tank itself with the Target World Location which will do the following:
	// Rotate the Turret. (Maybe implement a min/max turn angle)
	// Rotate the Barrel. (Maybe implement a min/max elevation angle)
}

void ATankPlayerController::PrintOutPossessedTankName()
{
	ATank* ptReqTank = GetControlledTank();
	if (ptReqTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController: Not possessing a Tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController: Possessing Tank '%s'"), *ptReqTank->GetName());
	}
}