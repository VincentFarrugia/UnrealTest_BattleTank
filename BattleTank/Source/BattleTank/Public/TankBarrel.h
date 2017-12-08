// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float i_relativeSpeedInDegPerSecond);

private:
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevationInDegrees = 60.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevationInDegrees = 0.0f;

	UPROPERTY(EditAnywhere, Category="Setup")
	float ElevationSpeed_CMPerSecond;
	
};
