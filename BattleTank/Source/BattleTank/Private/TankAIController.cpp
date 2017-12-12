// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* ptPlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ptMyTank = GetPawn();

	if (!ensure(ptPlayerTank && ptMyTank)) { return; }
		
	MoveToActor(ptPlayerTank, AcceptanceRadius);

	UTankAimingComponent* myAimingComponent = ptMyTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(myAimingComponent)) { return; }
	myAimingComponent->AimAt(ptPlayerTank->GetActorLocation());

	if (myAimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		myAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))	{ return; }

		// Subscribe our local method to the tank's death event.
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath()
{
	APawn* PossessedPawn = GetPawn();
	if (PossessedPawn)
	{
		PossessedPawn->DetachFromControllerPendingDestroy();
	}
}