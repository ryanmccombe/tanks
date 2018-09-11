// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

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
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) {
	OutHitLocation = FVector(1.0f);
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation,
		ViewportSizeY * CrosshairYLocation
	);

	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const {
	FVector CameraWorldLocation;
	FVector CameraWorldDirection;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			StartLocation + LookDirection * LineTraceRange,
			ECollisionChannel::ECC_Visibility
		)) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}
