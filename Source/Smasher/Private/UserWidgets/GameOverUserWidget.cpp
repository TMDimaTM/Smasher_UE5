// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/GameOverUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"



// Restarting current level
void UGameOverUserWidget::RestartLevel()
{
	FString CurrentMapName = GetWorld()->GetMapName();
	CurrentMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	UGameplayStatics::OpenLevel(this, FName(CurrentMapName));
}