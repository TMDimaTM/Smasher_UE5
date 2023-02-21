// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Total score text
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UTextBlock* GameScoreText;

	// Total score value
	UPROPERTY(BlueprintReadOnly)
	int32 TotalScore;

	// Restarting current level
	UFUNCTION(BlueprintCallable)
	void RestartLevel();

private:
	// Background image
	UPROPERTY(meta = (BindWidget))
	class UImage* BackgroundImage;

	// Game over text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameOverText;

	// Game restart button
	UPROPERTY(meta = (BindWidget))
	class UButton* GameRestartButton;

	// Game resatrt button text
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameRestartButtonText;
};
