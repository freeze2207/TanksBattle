// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevates(float RelativeSpeed)
{
	// Move the Barrel right amount of this frame

	// Given a max elevation speed and frame time

	/*UE_LOG(LogTemp, Warning, TEXT("Elevate at spped: %f"), RelativeSpeed);*/
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees), 0 , 0));
}