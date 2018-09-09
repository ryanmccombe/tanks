// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))

	auto Owner = GetControlledTank();
	if (!Owner) {
		UE_LOG(LogTemp, Error, TEXT("No possessed tank!"))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Possessed tank: %s"), *Owner->GetName())
	}
		
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}
