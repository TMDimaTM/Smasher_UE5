// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/WeaponActor.h"
#include "Actors/Projectiles/ProjectileActor.h"


// Sets default values for this actor's properties
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creating mesh component for rendering weapon's model
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(Mesh);
}