// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	// Called when the controller has just possessed a pawn.
	virtual void SetPawn(APawn* InPawn) override;

	// How close the AI tank will come to its target before stopping.
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 8000.0f;

private:
	UFUNCTION()
	void OnPossedTankDeath();
};