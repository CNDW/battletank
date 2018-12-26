// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ABattleTankGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float CrosshairPctX = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairPctY = 0.3333;
};
