// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Not Controlling any tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controlling tank %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation;
	if( GetSightRayHitLocation(HitLocation) )
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// De-project the screen position of the crosshair to a world direction  
	FVector LookDirection;

	FHitResult OUT HitResult;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		/*UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());*/
		// Line-trace along that LookDirection , and see what it hits (to max range)

		GetLookVectorHitLocation(LookDirection, HitResult);
		
	}

	HitLocation = HitResult.Location;

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraLocation; // To be discarded
	
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &LookDirection, FHitResult &HitResult) const
{
	FVector StartPosition = PlayerCameraManager->GetCameraLocation();

	/*DrawDebugLine(
		GetWorld(),
		StartPosition,
		StartPosition + LookDirection * LineTraceRange,
		FColor(255, 0, 0),
		false,
		0.0f,
		0,
		3.0f
	);*/

	if ( GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartPosition,
		StartPosition + LookDirection * LineTraceRange,
		ECollisionChannel::ECC_Visibility
	) ) {
		return true;
	}
	else
	{
		HitResult.Location = FVector(0);
		return	false;
	}
}
