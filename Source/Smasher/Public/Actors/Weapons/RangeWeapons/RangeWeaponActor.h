// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/WeaponActor.h"
#include "RangeWeaponActor.generated.h"



DECLARE_DELEGATE(FShotDelegate)

UENUM(BlueprintType)
enum EFireMode
{
	Auto,
	Single
};

UCLASS()
class SMASHER_API ARangeWeaponActor : public AWeaponActor
{
	GENERATED_BODY()

protected:
	// Common fire implementation
	void Fire(FShotDelegate ShotDelegate);

	// Common stop firing implementation
	void StopFiring();

	// Common change fire mode implementation
	void ChangeFireMode();
	
	// Common taking a shot logic
	void Shot();

protected:
	// Projectile class
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectileActor> Projectile;

	// Fire mode (auto, single)
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TEnumAsByte<EFireMode> FireMode;

	// Time between shots
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRate;

	// Muzzle flash effect
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* MuzzleFlash;

	// Camera shake effect
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> CameraShake;

	// Fire sound effect
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* FireSound;

	// Change fire mode sound effect
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ChangeFireModeSound;

	// Location and Rotation for spawning projectile
	FVector SpawnProjectileLocation;
	FRotator SpawnProjectileRotation;

	// Timer handle for starting and stopping automatic fire
	FTimerHandle FireTimerHandle;

	// Get muzzle socket transform
	FTransform GetMuzzleTransform() const;

	// Spawning the projectile
	void SpawnProjectile() const;
};
