// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player tank %s"), *PlayerTank->GetName())
	} else {
		UE_LOG(LogTemp, Error, TEXT("AI Controller cannot find a player tank!"))
	}
}

ATank* ATankAIController::GetControlledTank() {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}
