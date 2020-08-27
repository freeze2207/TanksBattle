// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKSBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevates(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5.0f; // Sensible Default
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 25.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.0f;
};
