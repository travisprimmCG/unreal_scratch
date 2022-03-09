// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
{
	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}


void UObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	ensureMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSubsystem::DisplayObjectiveWidget ObjectiveWidget is nullptr"));
	ObjectiveWidget->AddToViewport();
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription()
{
	if (!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive)
	{
		return TEXT("N/A");
	}

	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed)
	{
		RetObjective += TEXT(" Completed");
	}

	return RetObjective;
}

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComponent* ObjectiveComponent)
{
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize)
	{
		// Adding listener for when an Objective's state would complete as this is the World's overall ObjectiveSubsystem.
		// OnStateChanged() -->EVENT<-- is able to add listeners here, but it is only able to have .Broadcast() invoked for it in the UObjectiveComponent.
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComponent* ObjectiveComponent)
{
	Objectives.Remove(ObjectiveComponent);
}

/// <summary>
/// Called when when any registered Objective has a state changed. See registration process in AddObjective()
/// </summary>
/// <param name="ObjectiveComponent"></param>
/// <param name="ObjectiveState"></param>
void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState)
{
	DisplayObjectiveWidget();
}

