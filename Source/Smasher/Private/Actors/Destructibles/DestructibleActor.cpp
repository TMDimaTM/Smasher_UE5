// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Destructibles/DestructibleActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/SmasherGameModeBase.h"



// Sets default values
ADestructibleActor::ADestructibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creating mesh component for rendering destructible's model
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Mesh->SetSimulatePhysics(true);

	// Creating scene component to get location for object's explosion
	ExplosionSpawnPoint = CreateDefaultSubobject<USceneComponent>("Explosion Spawn Point");
	ExplosionSpawnPoint->SetupAttachment(Mesh);

	// Setting default values
	TotalHealth = 100.0f;
	TotalPoints = 10;
	TotalStylePoints = 10;
}

// Called when the game starts or when spawned
void ADestructibleActor::BeginPlay()
{
	Super::BeginPlay();

	// Getting game mode
	GameMode = Cast<ASmasherGameModeBase>(UGameplayStatics::GetGameMode(this));

	// Gettings current values from total values at start
	CurrentHealth = TotalHealth;
	CurrentPoints = TotalPoints;
	CurrentStylePoints = TotalStylePoints;

	// Binding taking damage function
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::TakeDamage);
}

// Calculating points after taking damage
void ADestructibleActor::CalculatePoints()
{
	int32 LastPoints = CurrentPoints;
	int32 LastStylePoints = CurrentStylePoints;

	CurrentPoints = (CurrentHealth / TotalHealth) * TotalPoints;
	CurrentStylePoints = (CurrentHealth / TotalHealth) * TotalStylePoints;

	if (GameMode != nullptr)
	{
		int32 PointsToAdd = (LastPoints - CurrentPoints) * GameMode->GetCurrentMultiplier();
		int32 StylePointsToAdd = LastStylePoints - CurrentStylePoints;

		GameMode->UpdateGameCondition(PointsToAdd, StylePointsToAdd);
	}
}

// Taking damage function
void ADestructibleActor::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth > 0)
	{
		CurrentHealth -= Damage;

		CalculatePoints();

		if (CurrentHealth <= 0)
		{
			if (ExplosionEffect != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, ExplosionSpawnPoint->GetComponentTransform());
			}

			if (ExplosionSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, ExplosionSpawnPoint->GetComponentLocation());
			}

			Destroy();
		}
	}
}

// Getting current health
float ADestructibleActor::GetCurrentHealth() const
{
	return CurrentHealth;
}

// Getting left points
int32 ADestructibleActor::GetPointsLeft() const
{
	return CurrentPoints;
}