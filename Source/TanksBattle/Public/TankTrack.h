// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  The TankTrack is used to set maximum driving force and apply force to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKSBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Set a throttle between 0 and 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max force per track , in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 3500000.0f;
};
