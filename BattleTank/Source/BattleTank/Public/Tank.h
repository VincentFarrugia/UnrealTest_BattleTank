// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* AimingComponent;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* MovementComponent;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

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
	UTankBarrel* Barrel = nullptr;

	double lastFireTime = 0.0f;
};
