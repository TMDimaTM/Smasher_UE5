// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDs/SmasherHUD.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgets/HUDUserWidget.h"



// Called when the game starts
void ASmasherHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWidgetClass);
	}
}

// Setting HUD visibility
void ASmasherHUD::SetVisibility(bool bVisible)
{
	if (HUDWidget != nullptr)
	{
		if (bVisible)
		{
			HUDWidget->AddToViewport();
		}
		else
		{
			HUDWidget->RemoveFromParent();
		}
	}
}