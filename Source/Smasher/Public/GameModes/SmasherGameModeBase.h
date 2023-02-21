// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SmasherGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API ASmasherGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	// Sets default values for this actor's properties
	ASmasherGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Starting match timer
	UFUNCTION(BlueprintCallable)
	void StartMatch();

	// Calculating session points
	void UpdateGameCondition(const int32& PointsToAdd, const int32& StylePointsToAdd);

	// Getting match time left value
	UFUNCTION(BlueprintPure)
	int32 GetMatchTimeLeft() const;

	// Getting all the earned points value
	UFUNCTION(BlueprintPure)
	int32 GetTotalPoints() const;

	// Getting current multiplier value
	UFUNCTION(BlueprintPure)
	int32 GetCurrentMultiplier() const;

private:
	// The time of the match in seconds
	UPROPERTY(EditDefaultsOnly, Category = "Game Start")
	int32 MatchTime;

	// Game start widget class
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UGameStartUserWidget> GameStartWidgetClass;
	UPROPERTY()
	UGameStartUserWidget* GameStartWidget;

	// Game over widget class
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UGameOverUserWidget> GameOverWidgetClass;
	UPROPERTY()
	UGameOverUserWidget* GameOverWidget;

	// Number of style points to reach the new multiplier
	UPROPERTY(EditDefaultsOnly, Category = "Multiplier")
	int32 FirstMultiplierStylePointsRequired;
	UPROPERTY(EditDefaultsOnly, Category = "Multiplier")
	int32 NextMultiplierStylePointsRequired;

	// Player controller
	UPROPERTY()
	class ASmasherPlayerController* PlayerController;

	// Player HUD
	UPROPERTY()
	class ASmasherHUD* HUD;

	// All the earned points value
	int32 TotalPoints;
	// All the earned style points value
	int32 TotalStylePoints;
	// Current points multiplier
	int32 CurrentMultiplier;

	// Match timer handle
	FTimerHandle MatchTimerHandle;

	// Multiplier time values
	float TotalMultiplierDrainTime;
	float CurrentMultiplierDrainTime;

	bool bDrainMultiplier;

	// Creating and adding game start widget to the screen
	void CreateGameStartWidget();

	// Calculating style points and multiplier
	void CalculateStylePointsMultiplier(const int32& StylePointsToAdd);

	// Increasing multiplier when enough style points
	void IncreaseMultiplier();

	// Calculate multiplier drain time depending on current multiplier value
	void CalculateMultiplierDrainTime();

	// Draining multiplier
	void DrainMultiplier(float DeltaTime);

	// Game over logic
	void GameOver();

	// Creating and adding game over widget to the screen
	void CreateGameOverWidget();
};