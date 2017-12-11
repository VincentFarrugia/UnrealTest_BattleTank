// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Camera/CameraActor.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category="Setup")
	ATank* GetControlledTank() const;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation_WidthPerc = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation_HeightPerc = 0.33333;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& o_hitLocation) const;
	void PrintOutPossessedTankName();
};
