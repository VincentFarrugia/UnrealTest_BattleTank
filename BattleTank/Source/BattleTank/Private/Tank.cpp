// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>("AimingComponent");
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	AimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	AimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{	
	FVector projectileSpawnPt = Barrel->GetSocketLocation(FName("BarrelEnd"));
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, projectileSpawnPt, FRotator::ZeroRotator);
	UE_LOG(LogTemp, Warning, TEXT("Tank: '%s' has fired its cannon!"), *GetName());
}

void ATank::AimAt(FVector i_aimPt)
{
	AimingComponent->AimAt(i_aimPt, LaunchSpeed);
}
