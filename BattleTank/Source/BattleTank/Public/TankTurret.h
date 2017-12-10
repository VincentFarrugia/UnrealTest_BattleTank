// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxTurnSpeedInDegPerSecond = 25.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinTurnYawDegrees = -80.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxTurnYawDegrees = 80.0f;
	
	void Turn(float i_relativeSpeedInDegPerSecond);
	
};
