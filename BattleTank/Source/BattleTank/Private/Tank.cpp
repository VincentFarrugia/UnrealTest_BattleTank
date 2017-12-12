// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, CurrentHealth);
	CurrentHealth -= damageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank '%s' was obliterated!"), *GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank '%s' health is: '%i'"), *GetName(), CurrentHealth);
	}
	return damageToApply;
}

float ATank::GetHealthPercent()
{
	return ((float)CurrentHealth / (float)StartingHealth);
}