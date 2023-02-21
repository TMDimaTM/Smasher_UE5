// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/RangeWeapons/RangeWeaponActor.h"
#include "Interfaces/WeaponInterface.h"
#include "ShotgunActor.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API AShotgunActor : public ARangeWeaponActor, public IWeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShotgunActor();

public:
	// Fire implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire();
	virtual void Fire_Implementation();

	// Stop firing implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopFiring();
	virtual void StopFiring_Implementation();

	// Change fire mode implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChangeFireMode();
	virtual void ChangeFireMode_Implementation();

private:
	// Number of bullets to be shooten at once
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 BulletsPerShot;

	// Maximum random angle for bullet direction
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float RandomBulletAngle;

	// Shot delegate
	FShotDelegate ShotDelegate;

	// Calculating random bullet rotation
	void SetRandomBulletDirection();

	// Taking a shot
	void Shot();
};
