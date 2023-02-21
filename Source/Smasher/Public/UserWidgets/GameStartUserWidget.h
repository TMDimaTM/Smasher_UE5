// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API UGameStartUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	// Background image
	UPROPERTY(meta = (BindWidget))
	class UImage* BackgroundImage;

	// Game start text
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameStartText;

	// Game description text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameDescriptionText;

	// Game start button
	UPROPERTY(meta = (BindWidget))
	class UButton* GameStartButton;

	// Game start button text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameStartButtonText;
};
