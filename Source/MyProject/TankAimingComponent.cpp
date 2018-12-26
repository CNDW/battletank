// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


UTankAimingComponent::UTankAimingComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrelComponent* _barrel, UTankTurretComponent* _turret) {
	barrel = _barrel;
	turret = _turret;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float now = GetWorld()->GetTimeSeconds();
	if (Ammo < 1) {
		firingState = EFiringState::Empty;
	}
	else if ((now - LastFireTime) <= ReloadTimeInSeconds) {
		firingState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		firingState = EFiringState::Aiming;
	}
	else {
		firingState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(barrel)) { return false; }
	auto forward = barrel->GetForwardVector();
	auto intended = IntendedAim.GetSafeNormal();
	return !forward.Equals(intended, 0.05f);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!barrel) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = barrel->GetSocketLocation(FName("ProjectileSpawn"));

	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	bool bIfHasVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bIfHasVelocity) {
		MoveBarrel(OutLaunchVelocity);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	IntendedAim = AimDirection;
	auto AimAsRotator = AimDirection.Rotation();
	if (barrel && turret) { 
		auto rotation = barrel->GetForwardVector().Rotation();
		auto deltaRotator = AimAsRotator - rotation;
		barrel->Elevate(deltaRotator.Pitch);
		if (FMath::Abs<float>(deltaRotator.Yaw) > 180.f) {
			turret->Rotate(-deltaRotator.Yaw);
		}
		else {
			turret->Rotate(deltaRotator.Yaw);
		}
	}
}

void UTankAimingComponent::Fire()
{
	if (!barrel) { return; }
	if (firingState > EFiringState::Aiming) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	LastFireTime = GetWorld()->GetTimeSeconds();
	Ammo--;

	firingState = Ammo < 1 ? EFiringState::Empty : EFiringState::Reloading;
	// spawn a projectile at location
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		barrel->GetSocketLocation(FName("ProjectileSpawn")),
		barrel->GetSocketRotation(FName("ProjectileSpawn"))
	);

	Projectile->LaunchProjectile(LaunchSpeed);
}
