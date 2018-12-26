// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;
class UTankTurretComponent;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Aiming,
	Reloading,
	Empty
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrelComponent * _barrel, UTankTurretComponent * _turret);
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	EFiringState GetFiringState() { return firingState; }
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = Firing)
	EFiringState firingState = EFiringState::Reloading;

	UFUNCTION(BlueprintCallable, Category = Firing)
	uint8 GetCurrentAmmo() { return Ammo; }

private:
	UTankBarrelComponent *barrel = nullptr;
	UTankTurretComponent *turret = nullptr;
	void MoveBarrel(FVector AimDirection);
	UTankAimingComponent();
	bool IsBarrelMoving();

	FVector IntendedAim = FVector(0);

	UPROPERTY(EditAnywhere, Category = Firing)
	uint8 Ammo = 5;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 4;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float LastFireTime = 0;
};
