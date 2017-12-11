// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrintOutPossessedTankName();
	UTankAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
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
	if (!ensure(GetControlledTank())) { return; }

	// Raycast crosshair to get the world location.

	FVector hitLocation;
	if (GetSightRayHitLocation(hitLocation))
	{
		// Call Aim on the Tank itself with the Target World Location which will do the following:
		// Rotate the Turret. (Maybe implement a min/max turn angle)
		// Rotate the Barrel. (Maybe implement a min/max elevation angle)

		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& o_hitLocation) const
{
	bool didHitSomething = false;
	ATank* ptPlayerTank = GetControlledTank();
	if (ptPlayerTank)
	{
		int32 viewportWidth, viewportHeight;
		GetViewportSize(viewportWidth, viewportHeight);
		FVector2D crosshairScreenLocation(CrossHairXLocation_WidthPerc * viewportWidth, CrossHairYLocation_HeightPerc * viewportHeight);
		FVector crosshairPtInWorldSpace;
		FVector crosshairForwardVector;		
		DeprojectScreenPositionToWorld(crosshairScreenLocation.X, crosshairScreenLocation.Y, crosshairPtInWorldSpace, crosshairForwardVector);

		FVector rayExtentPt = crosshairPtInWorldSpace + (crosshairForwardVector * 99999.0f);
		FHitResult rayHitResult;
		didHitSomething = GetWorld()->LineTraceSingleByChannel(rayHitResult, crosshairPtInWorldSpace, rayExtentPt, ECollisionChannel::ECC_Visibility);

		if (didHitSomething)
		{
			o_hitLocation = rayHitResult.ImpactPoint;
		}
		else
		{
			o_hitLocation = FVector::ZeroVector;
		}
	}
	return didHitSomething;
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