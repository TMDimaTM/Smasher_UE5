// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Destructibles/DestructibleActor.h"



// Constructor
APlayerCharacter::APlayerCharacter()
{
	// Activates tick function
	PrimaryActorTick.bCanEverTick = true;

	// Setting up spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SocketOffset = FVector(0.0f, 50.0f, 75.0f);
	SpringArm->SetupAttachment(RootComponent);

	// Setting up camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

	// Camera bindings
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	// Sprint bindings
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ThisClass::SprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ThisClass::SprintReleased);

	// Jump bidings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Fire bindings
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ThisClass::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ThisClass::StopFiring);

	// Change weapon binding
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &ThisClass::ChangeWeapon);

	// Change fire mode binding
	PlayerInputComponent->BindAction("ChangeFireMode", IE_Pressed, this, &ThisClass::ChangeFireMode);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	CheckForSelectedObject();
}

// Move forward input
void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

// Move right input
void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

// Sprint press input
void APlayerCharacter::SprintPressed()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMaxSpeed;

	StopFiring();
}

// Sprint release input
void APlayerCharacter::SprintReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed;
}

// Checking if player is looking at any destructialbe objects
void APlayerCharacter::CheckForSelectedObject()
{
	FHitResult HitResult;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector StartLocation = PlayerViewPointLocation;
	FVector EndLocation = PlayerViewPointRotation.Vector() * 2500 + StartLocation;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Destructible);
	if (bHit)
	{
		if (ADestructibleActor* HitActor = Cast<ADestructibleActor>(HitResult.GetActor()))
		{
			SelectedActor = HitActor;
		}
		else
		{
			SelectedActor = nullptr;
		}
	}
	else
	{
		SelectedActor = nullptr;
	}
}
