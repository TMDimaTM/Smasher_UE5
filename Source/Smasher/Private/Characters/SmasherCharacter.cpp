// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SmasherCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Weapons/WeaponActor.h"
#include "Interfaces/WeaponInterface.h"



// Sets default values
ASmasherCharacter::ASmasherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASmasherCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponActorClasses.Num() > 0)
	{
		SpawnWeapons();
		SetStartWeapon();
	}
}

// Spawning all the weapons available to use
void ASmasherCharacter::SpawnWeapons()
{
	FTransform SocketTransform = GetMesh()->GetSocketTransform("rifle_r");

	for (int32 i = 0; i < WeaponActorClasses.Num(); i++)
	{
		AWeaponActor* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponActor>(WeaponActorClasses[i], SocketTransform);
		SpawnedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "rifle_r");
		SpawnedWeapon->SetOwner(this);

		UsableWeapons.Add(SpawnedWeapon);
	}
}

// Setting start weapons for character
void ASmasherCharacter::SetStartWeapon()
{
	for (int32 i = 1; i < UsableWeapons.Num(); i++)
	{
		UsableWeapons[i]->SetActorHiddenInGame(true);
	}
	CurrentWeapon = UsableWeapons[0];
}

// Checking if character is sprinting or not
bool ASmasherCharacter::IsSprinting() const
{
	return GetVelocity().Length() >= SprintMaxSpeed - 10.0f;
}

// Fire function
void ASmasherCharacter::Fire()
{
	if (IWeaponInterface* Interface = Cast<IWeaponInterface>(CurrentWeapon))
	{
		if (!IsSprinting())
		{
			Interface->Execute_Fire(CurrentWeapon);
		}
	}
}

// Stop firing function
void ASmasherCharacter::StopFiring()
{
	if (IWeaponInterface* Interface = Cast<IWeaponInterface>(CurrentWeapon))
	{
		Interface->Execute_StopFiring(CurrentWeapon);
	}
}

// Change weapon function
void ASmasherCharacter::ChangeWeapon()
{
	StopFiring();

	CurrentWeapon->SetActorHiddenInGame(true);

	if (CurrentWeaponIndex >= UsableWeapons.Num() - 1)
	{
		CurrentWeaponIndex = 0;
	}
	else
	{
		CurrentWeaponIndex++;
	}

	CurrentWeapon = UsableWeapons[CurrentWeaponIndex];
	CurrentWeapon->SetActorHiddenInGame(false);

	if (ChangeWeaponSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ChangeWeaponSound, GetActorLocation());
	}
}

// Change fire mode function
void ASmasherCharacter::ChangeFireMode()
{
	if (IWeaponInterface* Interface = Cast<IWeaponInterface>(CurrentWeapon))
	{
		Interface->Execute_ChangeFireMode(CurrentWeapon);
	}
}