// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovementComponent;

public:	

	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	void AimAt(FVector i_aimPt);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000; // In cm per second.

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	double reloadTimeInSeconds = 3.0f;

private:

	double lastFireTime = 0.0f;

	UTankBarrel* Barrel = nullptr;
};
