// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PrintOutPossessedTankName();
	
	ATank* ptReqPlayerTank = GetPlayerTank();
	if (!ptReqPlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank '%s' did not find player tank"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank '%s' found player tank '%s'"), *GetName(), *ptReqPlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{

}

ATank* ATankAIController::GetPossessedTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	APlayerController* ptFirstPlayerController = GetWorld()->GetFirstPlayerController();
	if (!ptFirstPlayerController)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(ptFirstPlayerController->GetPawn());
	}
}

void ATankAIController::PrintOutPossessedTankName()
{
	ATank* ptReqTank = GetPossessedTank();
	if (!ptReqTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController: Not possessing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController: Possessing Tank '%s'"), *ptReqTank->GetName());
	}
}
