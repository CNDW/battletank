// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class MYPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = AI)
	float AcceptanceRadius = 3000;
	
	UTankAimingComponent *AimingComponent = nullptr;
};
