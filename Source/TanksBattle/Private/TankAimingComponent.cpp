// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet)
	{
		return;
	}
	Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet)
	{
		return;
	}
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetAimingLocation, float LaunchSpeed)
{
	auto CurrentTankName = GetOwner()->GetName();
	
	auto BarrelLocation = Barrel->GetComponentLocation();
	/*UE_LOG(LogTemp, Warning, TEXT("%s is aming at location: %s from %s"), *CurrentTankName, *TargetAimingLocation.ToString(), *BarrelLocation.ToString());*/

	if (!Barrel || !Turret) 
	{
		return;
	}

	FVector OUT LaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		TargetAimingLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	// Calculate LaunchVelocity
	if (bHaveAimSolution)
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f Aim solution found"), Time);
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f No Aim solution found"), Time);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Difference between current Barrel rotation and the target rotation 
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;

	Barrel->Elevates(DeltaRotator.Pitch);
	Turret->Spin(DeltaRotator.Yaw);
}
