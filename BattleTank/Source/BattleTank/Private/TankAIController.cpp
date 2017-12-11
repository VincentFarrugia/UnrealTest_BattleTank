// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"



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
	myAimingComponent->Fire();
}