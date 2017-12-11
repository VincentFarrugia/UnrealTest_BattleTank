// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	UE_LOG(LogTemp, Warning, TEXT("CENSUTEST: ATank C++ Constructor called."));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("CENSUTEST: ATank C++ BeginPlay called."));
}

void ATank::Fire()
{		
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;

	if ((Barrel)&&(isReloaded))
	{
		AProjectile* ptNwProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelEnd")),
			Barrel->GetSocketRotation(FName("BarrelEnd"))
			);

		ptNwProjectile->LaunchProjectile(LaunchSpeed);
		lastFireTime = FPlatformTime::Seconds();

		UE_LOG(LogTemp, Warning, TEXT("Tank: '%s' has fired its cannon!"), *GetName());
	}
}

void ATank::AimAt(FVector i_aimPt)
{
	if (!AimingComponent) { return; }
	AimingComponent->AimAt(i_aimPt, LaunchSpeed);
}
