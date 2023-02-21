// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/RangeWeapons/ShotgunActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"



// Sets default values for this actor's properties
AShotgunActor::AShotgunActor()
{
	// Binding shot delegate
	ShotDelegate.BindUObject(this, &ThisClass::Shot);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Default fire mode
	FireMode = EFireMode::Single;

	// Default time between shots
	FireRate = 0.5f;

	// Default number of bullets to be shooten at once
	BulletsPerShot = 5;

	// Default maximum random angle for bullet direction
	RandomBulletAngle = 2.0f;
}

// Fire implementation
void AShotgunActor::Fire_Implementation()
{
	Super::Fire(ShotDelegate);

}

// Stop firing implementation
void AShotgunActor::StopFiring_Implementation()
{
	Super::StopFiring();

}

// Change fire mode implementation
void AShotgunActor::ChangeFireMode_Implementation()
{
	Super::ChangeFireMode();

}

// Calculating random bullet rotation
void AShotgunActor::SetRandomBulletDirection()
{
	if (UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>())
	{
		SpawnProjectileLocation = GetMuzzleTransform().GetLocation();

		FVector Direction = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(Camera->GetForwardVector(), RandomBulletAngle);
		SpawnProjectileRotation = Direction.Rotation();
	}
}

// Taking a shot
void AShotgunActor::Shot()
{
	Super::Shot();

	for (int32 i = 0; i < BulletsPerShot; i++)
	{
		SetRandomBulletDirection();
		SpawnProjectile();
	}
}