// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmasherCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SMASHER_API APlayerCharacter : public ASmasherCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:
	// Selected object we are current looking at
	UPROPERTY(BlueprintReadOnly)
	class ADestructibleActor* SelectedActor;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Spring arm component for checking obstacles between player and camera
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	// Camera component for player's vision
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	// Movement inputs
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	// Sprint inputs
	void SprintPressed();
	void SprintReleased();

	// Checking if player is looking at any destructialbe objects
	void CheckForSelectedObject();
};
