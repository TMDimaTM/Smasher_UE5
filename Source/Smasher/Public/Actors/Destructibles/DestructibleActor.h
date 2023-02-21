// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleActor.generated.h"

UCLASS()
class SMASHER_API ADestructibleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Getting current health
	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() const;

	// Getting left points
	UFUNCTION(BlueprintPure)
	int32 GetPointsLeft() const;

private:

	// Mesh for rendering destructible's model
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	// Mesh for rendering destructible's model
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ExplosionSpawnPoint;

	// Total and current health values
	UPROPERTY(EditAnywhere, Category = "Health")
	float TotalHealth;
	float CurrentHealth;

	// Total and current point values
	UPROPERTY(EditAnywhere, Category = "Points")
	int32 TotalPoints;
	int32 CurrentPoints;

	// Total and current style point values
	UPROPERTY(EditAnywhere, Category = "Points")
	int32 TotalStylePoints;
	int32 CurrentStylePoints;

	// Explosion effect
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ExplosionEffect;

	// Explosion sound effect
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ExplosionSound;

	// Game mode pointer
	UPROPERTY()
	class ASmasherGameModeBase* GameMode;

	// Calculating points after taking damage
	void CalculatePoints();

	// Taking damage function
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};