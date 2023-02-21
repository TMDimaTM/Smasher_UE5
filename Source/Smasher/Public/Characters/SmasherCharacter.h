// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SmasherCharacter.generated.h"

UCLASS()
class SMASHER_API ASmasherCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASmasherCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Maximum default and sprint speed values
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float DefaultMaxSpeed = 375.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintMaxSpeed = 500.0f;

	// Fire functions
	void Fire();
	void StopFiring();

	// Change weapon function
	void ChangeWeapon();

	// Change fire mode function
	void ChangeFireMode();

private:
	// All the weapons classes to wield
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TArray<TSubclassOf<class AWeaponActor>> WeaponActorClasses;

	UPROPERTY()
	TArray<AWeaponActor*> UsableWeapons;

	// Change weapon sound effect
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ChangeWeaponSound;

	// Current weapon
	UPROPERTY()
	AActor* CurrentWeapon;

	int32 CurrentWeaponIndex;

	// Checking if character is sprinting or not
	bool IsSprinting() const;

	// Spawning and setting character's weapons
	void SpawnWeapons();
	void SetStartWeapon();
};
