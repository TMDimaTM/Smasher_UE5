// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/SmasherGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "HUDs/SmasherHUD.h"
#include "UserWidgets/GameStartUserWidget.h"
#include "UserWidgets/GameOverUserWidget.h"
#include "PlayerControllers/SmasherPlayerController.h"



// Sets default values for this actor's properties
ASmasherGameModeBase::ASmasherGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setting default value for match duration
	MatchTime = 60;

	// Setting default values requiered to achieve new multiplier
	FirstMultiplierStylePointsRequired = 100;
	NextMultiplierStylePointsRequired = 50;

	// Setting default value for earned points
	TotalPoints = 0;
	// Setting default value for earned style points
	TotalStylePoints = 0;
	// Setting default point multiplier
	CurrentMultiplier = 1;
}

// Called when the game starts or when spawned
void ASmasherGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Disabling player input at start
	PlayerController = Cast<ASmasherPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController != nullptr)
	{
		PlayerController->SetPlayerInputEnabled(false);
	}

	HUD = Cast<ASmasherHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	CreateGameStartWidget();
}

// Called every frame
void ASmasherGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDrainMultiplier)
	{
		DrainMultiplier(DeltaTime);
	}
}

// Creating and adding game start widget to the screen
void ASmasherGameModeBase::CreateGameStartWidget()
{
	if (GameStartWidgetClass)
	{
		GameStartWidget = CreateWidget<UGameStartUserWidget>(GetWorld(), GameStartWidgetClass);
		GameStartWidget->AddToViewport();
	}
}

// Starting match timer
void ASmasherGameModeBase::StartMatch()
{
	if (PlayerController != nullptr)
	{
		PlayerController->SetPlayerInputEnabled(true);
	}

	if (HUD != nullptr)
	{
		HUD->SetVisibility(true);
	}

	// Match countdown
	GetWorldTimerManager().SetTimer(MatchTimerHandle, this, &ThisClass::GameOver, MatchTime, false);
}

// Calculating session points
void ASmasherGameModeBase::UpdateGameCondition(const int32& PointsToAdd, const int32& StylePointsToAdd)
{
	TotalPoints += PointsToAdd;
	
	CalculateStylePointsMultiplier(StylePointsToAdd);
}

// Calculating style points and multiplier
void ASmasherGameModeBase::CalculateStylePointsMultiplier(const int32& StylePointsToAdd)
{
	if (CurrentMultiplier < 10)
	{
		TotalStylePoints += StylePointsToAdd;

		if (CurrentMultiplier == 1)
		{
			if (TotalStylePoints >= FirstMultiplierStylePointsRequired)
			{
				IncreaseMultiplier();
			}
		}
		else
		{
			if (TotalStylePoints >= NextMultiplierStylePointsRequired)
			{
				IncreaseMultiplier();
			}
		}
	}

	CurrentMultiplierDrainTime = TotalMultiplierDrainTime;	// Refresh multiplier drain time
}

// Increasing multiplier when enough style points
void ASmasherGameModeBase::IncreaseMultiplier()
{
	CurrentMultiplier++;
	TotalStylePoints = 0;

	CalculateMultiplierDrainTime();
	CurrentMultiplierDrainTime = TotalMultiplierDrainTime;
	bDrainMultiplier = true;
}

// Calculate multiplier drain time depending on current multiplier value
void ASmasherGameModeBase::CalculateMultiplierDrainTime()
{
	switch (CurrentMultiplier)
	{
		case 2:
			TotalMultiplierDrainTime = 15.0f;
			break;

		case 3:
			TotalMultiplierDrainTime = 10.0f;
			break;

		case 4:
			TotalMultiplierDrainTime = 7.0f;
			break;

		case 5:
			TotalMultiplierDrainTime = 5.0f;
			break;

		case 6:
			TotalMultiplierDrainTime = 4.0f;
			break;

		case 7:
			TotalMultiplierDrainTime = 3.0f;
			break;

		case 8:
			TotalMultiplierDrainTime = 2.0f;
			break;

		case 9:
			TotalMultiplierDrainTime = 1.0f;
			break;

		case 10:
			TotalMultiplierDrainTime = 0.5f;
			break;

		default:
			bDrainMultiplier = false;
			break;
	}
}

// Draining multiplier
void ASmasherGameModeBase::DrainMultiplier(float DeltaTime)
{
	CurrentMultiplierDrainTime -= DeltaTime;
	if (CurrentMultiplierDrainTime <= 0.0f)
	{
		CurrentMultiplier--;
		bDrainMultiplier = false;

		if (CurrentMultiplier > 1 && CurrentMultiplier < 10)
		{
			CalculateMultiplierDrainTime();
			CurrentMultiplierDrainTime = TotalMultiplierDrainTime;
			bDrainMultiplier = true;
		}
	}
}

// Getting all the earned points
int32 ASmasherGameModeBase::GetTotalPoints() const
{
	return TotalPoints;
}

// Getting current multiplier value
int32 ASmasherGameModeBase::GetCurrentMultiplier() const
{
	return CurrentMultiplier;
}

// Getting match time left value
int32 ASmasherGameModeBase::GetMatchTimeLeft() const
{
	return GetWorldTimerManager().GetTimerRemaining(MatchTimerHandle);
}

// Game over logic
void ASmasherGameModeBase::GameOver()
{
	if (PlayerController != nullptr)
	{
		PlayerController->SetPlayerInputEnabled(false);
	}

	if (HUD != nullptr)
	{
		HUD->SetVisibility(false);
	}

	CreateGameOverWidget();
}

// Creating and adding game over widget to the screen
void ASmasherGameModeBase::CreateGameOverWidget()
{
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOverUserWidget>(GetWorld(), GameOverWidgetClass);
		GameOverWidget->TotalScore = TotalPoints;
		GameOverWidget->AddToViewport();
	}
}