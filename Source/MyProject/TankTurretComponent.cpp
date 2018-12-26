// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"

void UTankTurretComponent::Rotate(float RelativeSpeed) {
	auto Speed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto RotationChange = Speed * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, newRotation, 0.f));
}