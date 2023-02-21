// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Selected object's current health
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* SelectedObjectHealth;

	// Selected object's current points left
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* SelectedObjectPoints;

private:
	// Current aim image
	UPROPERTY(meta = (BindWidget))
	class UImage* AimImage;

	// Session time text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;

	// Total points text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PointsText;

	// Current multiplier text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MultiplierText;
};
