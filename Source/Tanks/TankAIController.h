// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"


UCLASS()
class TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

	void BeginPlay() override;
	ATank* GetControlledTank();
	ATank* GetPlayerTank();
	
	
};
