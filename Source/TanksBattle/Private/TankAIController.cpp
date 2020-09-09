// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());

	PlayerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	if (PlayerControlledTank && ControlledTank)
	{
		FVector PlayerLocation = PlayerControlledTank->GetActorLocation();
		// TODO move towards player? 

		//Aim at player
		ControlledTank->AimAt(PlayerLocation);

		// TODO Fire when ready
		ControlledTank->Fire();
		
	}
	
}
