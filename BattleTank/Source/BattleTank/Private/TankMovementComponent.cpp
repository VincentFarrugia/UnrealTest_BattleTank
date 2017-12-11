// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{
	LeftTrack->SetThrottle(-FMath::Abs(Throw));
	RightTrack->SetThrottle(-FMath::Abs(Throw));
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector aiForwardIntention = MoveVelocity.GetSafeNormal();
	FVector tankForwardVect = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float dotProdRes = FVector::DotProduct(aiForwardIntention, tankForwardVect);
	IntendMoveForward(dotProdRes);

	FVector crossProdRes = FVector::CrossProduct(tankForwardVect, aiForwardIntention);
	IntendTurnRight(crossProdRes.Z);
}