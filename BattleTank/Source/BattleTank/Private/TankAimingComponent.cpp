// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* i_ptBarrelToSet)
{
	Barrel = i_ptBarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector i_aimPt, float i_launchSpeedInCMPerSecond)
{	
	if (!Barrel) { return; }

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
		i_launchSpeedInCMPerSecond,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		responseParams,
		actorsToIgnore,
		true		
	);

	if (projectileVelocityFound)
	{
		FVector aimDirection = launchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);

		UE_LOG(LogTemp, Warning, TEXT("Tank '%s' is aiming at: '%s' from '%s'"),
			*(GetOwner()->GetName()),
			*(i_aimPt.ToString()),
			*(Barrel->GetComponentLocation().ToString()));
	}	
}

void UTankAimingComponent::MoveBarrel(FVector i_aimDirection)
{
	FRotator currentBarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator aimAsRotator = i_aimDirection.Rotation();
	FRotator deltaRotator = aimAsRotator - currentBarrelRotation;

	
	Barrel->Elevate(deltaRotator.Pitch);
}