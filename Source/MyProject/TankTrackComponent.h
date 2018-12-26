// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * Tank track is used to apply motion to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
	float CurrentThrottle = 0.f;

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysFriction();
	void DriveTrack();
	
public:
	UTankTrackComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000.0f;
};
