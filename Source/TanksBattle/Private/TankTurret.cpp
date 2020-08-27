// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Spin(float RelativeSpeed)
{
	// Move the Barrel right amount of this frame

	// Given a max elevation speed and frame time

	/*UE_LOG(LogTemp, Warning, TEXT("Elevate at spped: %f"), RelativeSpeed);*/
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto SpinAngleChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewSpinAngle = RelativeRotation.Yaw + SpinAngleChange;

	SetRelativeRotation(FRotator(0, RawNewSpinAngle, 0));
}