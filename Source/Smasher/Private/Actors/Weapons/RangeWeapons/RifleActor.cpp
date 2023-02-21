// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/RangeWeapons/RifleActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"



// Sets default values for this actor's properties
ARifleActor::ARifleActor()
{
	// Binding shot delegate
	ShotDelegate.BindUObject(this, &ThisClass::Shot);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Default fire mode
	FireMode = EFireMode::Auto;

	// Default time between shots
	FireRate = 0.1f;
}

// Fire implementation
void ARifleActor::Fire_Implementation()
{
	Super::Fire(ShotDelegate);

}

// Stop firing implementation
void ARifleActor::StopFiring_Implementation()
{
	Super::StopFiring();

}

// Change fire mode implementation
void ARifleActor::ChangeFireMode_Implementation()
{
	Super::ChangeFireMode();

}

// Taking a shot
void ARifleActor::Shot()
{
	Super::Shot();

	if (UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>())
	{
		FVector StartLocation;
		FVector EndLocation;

		FHitResult HitResult;

		StartLocation = Camera->GetComponentLocation();
		EndLocation = Camera->GetForwardVector() * 99999.0f + StartLocation;

		SpawnProjectileLocation = GetMuzzleTransform().GetLocation();

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility);
		if (bHit)
		{
			SpawnProjectileRotation = UKismetMathLibrary::FindLookAtRotation(SpawnProjectileLocation, HitResult.ImpactPoint);
		}
		else
		{
			SpawnProjectileRotation = Camera->GetComponentRotation();
		}

		SpawnProjectile();
	}
}