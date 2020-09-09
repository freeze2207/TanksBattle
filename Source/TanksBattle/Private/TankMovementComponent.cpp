// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// avoid dual acceleration on both input
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Tank Right intend: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// avoid dual acceleration on both input
}