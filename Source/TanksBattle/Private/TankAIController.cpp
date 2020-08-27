// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerControlledTank = GetPlayerTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Not Controlling any tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controlling tank %s"), *ControlledTank->GetName());
	}

	if (!PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not finding any player controlled tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI finding player controlled tank: %s"), *PlayerControlledTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	if (GetPlayerTank())
	{
		FVector PlayerLocation = GetPlayerTank()->GetActorLocation();
		// TODO move towards player? 
		//Aim at player
		GetControlledTank()->AimAt(PlayerLocation);
		// TODO Fire when ready
	}
	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerControlledTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerControlledTank) {
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerControlledTank);
	}
	
}