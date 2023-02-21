// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/RangeWeapons/RangeWeaponActor.h"
#include "Interfaces/WeaponInterface.h"
#include "RifleActor.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API ARifleActor : public ARangeWeaponActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARifleActor();

public:
	// Fire implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire();
	virtual void Fire_Implementation() override;

	// Stop firing implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StopFiring();
	virtual void StopFiring_Implementation() override;

	// Change fire mode implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChangeFireMode();
	virtual void ChangeFireMode_Implementation() override;

private:
	// Shot delegate
	FShotDelegate ShotDelegate;

	// Taking a shot
	void Shot();
};
