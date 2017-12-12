// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth <= 0) { return 0.0f; }

	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, CurrentHealth);
	CurrentHealth -= damageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return damageToApply;
}

float ATank::GetHealthPercent()
{
	return ((float)CurrentHealth / (float)StartingHealth);
}