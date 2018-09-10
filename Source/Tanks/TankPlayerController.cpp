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

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return;  }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) {
	OutHitLocation = FVector(1.0f);
	return true;
}
