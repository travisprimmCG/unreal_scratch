// Copyright Epic Games, Inc. All Rights Reserved.


#include "primm_scratchGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ObjectiveWorldSubsystem.h"

void Aprimm_scratchGameModeBase::StartPlay()
{
	Super::StartPlay();
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}
}