// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SmasherPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API ASmasherPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Setting player input state
	void SetPlayerInputEnabled(bool bEnabled);
};
