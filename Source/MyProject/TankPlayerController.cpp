// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "BattleTankGameMode.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();

	if (!ControlledTank) { return; }
	
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"))
	}
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	AimTowardCrosshair();
}

bool ATankPlayerController::GetSightRayHitLocation(FHitResult &HitResult) {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	ABattleTankGameMode *GameMode = (ABattleTankGameMode*)GetWorld()->GetAuthGameMode();

	FVector2D screenLocation = FVector2D(ViewportSizeX * GameMode->CrosshairPctX, ViewportSizeY * GameMode->CrosshairPctY);
	FVector LookDirection;

	if (!GetLookDirection(screenLocation, LookDirection)) {
		return false;
	}

	return GetHitLookDirection(HitResult, LookDirection);
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector &LookDirection)
{
	FVector WorldLocation;
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, WorldLocation, LookDirection)) {
		
		return true;
	}
	return false;
}

bool ATankPlayerController::GetHitLookDirection(FHitResult &HitResult, FVector &LookDirection)
{
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (LookDirection * LineTraceRange);
	bool result = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECollisionChannel::ECC_Visibility
	);
	
	return result;
}

void ATankPlayerController::AimTowardCrosshair() {
	if (!AimingComponent) {
		return;
	}

	FHitResult Hit;
	if (GetSightRayHitLocation(Hit)) {
		AimingComponent->AimAt(Hit.Location);
	}
}

