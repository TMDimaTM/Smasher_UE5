// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SmasherHUD.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API ASmasherHUD : public AHUD
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Setting HUD visibility
	void SetVisibility(bool bVisible);

private:
	// HUD widget class
	UPROPERTY(EditDefaultsOnly, Category = "User Widgets")
	TSubclassOf<class UHUDUserWidget> HUDWidgetClass;

	UPROPERTY()
	UHUDUserWidget* HUDWidget;
};
