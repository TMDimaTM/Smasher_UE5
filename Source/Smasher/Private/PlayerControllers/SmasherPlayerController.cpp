// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/SmasherPlayerController.h"

// Setting player input state
void ASmasherPlayerController::SetPlayerInputEnabled(bool bEnabled)
{
	APawn* OwnPawn = GetPawn();

	if (bEnabled)
	{
		OwnPawn->EnableInput(this);
	}
	else
	{
		OwnPawn->DisableInput(this);
	}

	bShowMouseCursor = !bEnabled;
	OwnPawn->SetActorTickEnabled(bEnabled);
}