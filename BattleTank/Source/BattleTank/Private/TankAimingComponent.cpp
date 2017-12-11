// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// Make sure that we start off by reloading.
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if((FPlatformTime::Seconds() - LastFireTime) < reloadTimeInSeconds)
	{
		firingStatus = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving())
	{
		firingStatus = EFiringStatus::Aiming;
	}
	else
	{
		firingStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector i_aimPt)
{	
	if (!ensure(Barrel && Turret)) { return; }

	FVector launchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("BarrelEnd"));
	FCollisionResponseParams responseParams;
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(GetOwner());
	bool projectileVelocityFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		i_aimPt,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		responseParams,
		actorsToIgnore,
		false
	);

	FVector aimDirection = launchVelocity.GetSafeNormal();
	MostRecentAimAtNormVect = aimDirection;

	if (projectileVelocityFound)
	{		
		MoveTurret(aimDirection);
		MoveBarrel(aimDirection);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return (!(MostRecentAimAtNormVect.Equals(Barrel->GetForwardVector().GetSafeNormal(), 0.01f)));
}

void UTankAimingComponent::MoveTurret(FVector i_aimDirection)
{
	FRotator currentTurretRotation = Turret->GetForwardVector().Rotation();
	FRotator aimAsRotator = i_aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - currentTurretRotation;
	Turret->Turn(deltaRotator.Yaw);
}

void UTankAimingComponent::MoveBarrel(FVector i_aimDirection)
{
	FRotator currentBarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = i_aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - currentBarrelRotation;
	Barrel->Elevate(deltaRotator.Pitch);
}

void UTankAimingComponent::Fire()
{
	if (firingStatus != EFiringStatus::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		AProjectile* ptNwProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelEnd")),
			Barrel->GetSocketRotation(FName("BarrelEnd"))
			);

		ptNwProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		firingStatus = EFiringStatus::Reloading;
	}
}