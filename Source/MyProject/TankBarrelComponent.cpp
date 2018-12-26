// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"

void UTankBarrelComponent::Elevate(float RelativeSpeed) {
	auto Speed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = Speed * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto newElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(newElevation, 0.f, 0.f));
}