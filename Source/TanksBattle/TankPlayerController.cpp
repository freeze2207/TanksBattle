// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TanksBattle.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Controlling any tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlling tank %s"), *ControlledTank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}