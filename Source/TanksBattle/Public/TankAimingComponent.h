// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

// Holds Barrels properties and elevates method 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKSBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	// Called when the game starts
	virtual void BeginPlay() override;
	void MoveBarrelTowards(FVector AimDirection);
	// Sets default values for this component's properties
	UTankAimingComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	void AimAt(FVector TargetAimingLocation, float LaunchSpeed);
	
};
