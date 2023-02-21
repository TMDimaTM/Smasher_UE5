// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/RangeWeapons/RangeWeaponActor.h"
#include "Actors/Projectiles/ProjectileActor.h"
#include "Kismet/GameplayStatics.h"



// Common fire implementation
void ARangeWeaponActor::Fire(FShotDelegate ShotDelegate)
{
	switch (FireMode)
	{
	case Auto:
		ShotDelegate.Execute();
		GetWorldTimerManager().SetTimer(FireTimerHandle, ShotDelegate, FireRate, true);
		break;

	case Single:
		ShotDelegate.Execute();
		break;
	}
}

// Common stop firing implementation
void ARangeWeaponActor::StopFiring()
{
	switch (FireMode)
	{
	case Auto:
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
		break;
	}
}

// Common change fire mode implementation
void ARangeWeaponActor::ChangeFireMode()
{
	if (!GetWorldTimerManager().IsTimerActive(FireTimerHandle))
	{
		if (FireMode == Auto)
		{
			FireMode = Single;
		}
		else
		{
			FireMode = Auto;
		}

		if (ChangeFireModeSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ChangeFireModeSound, GetActorLocation());
		}
	}
}

// Common taking a shot logic
void ARangeWeaponActor::Shot()
{
	if (MuzzleFlash != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, GetMuzzleTransform());
	}

	if (CameraShake)
	{
		UGameplayStatics::PlayWorldCameraShake(this, CameraShake, GetActorLocation(), 0.0f, 500.0f);
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetMuzzleTransform().GetLocation());
	}
}

// Get muzzle socket transform
FTransform ARangeWeaponActor::GetMuzzleTransform() const
{
	return Mesh->GetSocketTransform("MuzzleFlashSocket");
}

// Spawning the projectile
void ARangeWeaponActor::SpawnProjectile() const
{
	AActor* SpawnedProjectile = GetWorld()->SpawnActor<AProjectileActor>(Projectile, SpawnProjectileLocation, SpawnProjectileRotation);
	SpawnedProjectile->SetOwner(GetOwner());
}