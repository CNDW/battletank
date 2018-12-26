// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class MYPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent *aimingComponent);

private:
	bool GetSightRayHitLocation(FHitResult &HitResult);
	bool GetLookDirection(FVector2D screenLocation, FVector &LookDirection);
	bool GetHitLookDirection(FHitResult &HitResult, FVector &LookDirection);
	void AimTowardCrosshair();

	UTankAimingComponent *AimingComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
