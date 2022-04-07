// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActorComponent.h"
#include "InteractableDoor.h"

#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

#include "ObjectiveWorldSubsystem.h"

#include "DrawDebugHelpers.h"

constexpr float FLT_METERS(float meters) { return meters * 100.0f; }


static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("Abstraction.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle DoorInteractionComponent debug display."),
	ECVF_Default);


// Sets default values for this component's properties
UDoorActorComponent::UDoorActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DoorState = EDoorState::DS_Closed;

	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorActorComponent::OnDebugToggled));
}


// Called when the game starts
void UDoorActorComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = StartRotation + DesiredRotation;

	CurrentRotationTime = 0.0f;
}


// Called every frame
void UDoorActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DoorState == EDoorState::DS_Closed)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstPlayerController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				DoorState = EDoorState::DS_Opening;
				CurrentRotationTime = 0.0f;
			}
		}
	}
	else if (DoorState == EDoorState::DS_Opening)
	{
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
		if (TimeRatio >= 1.0f)
		{
			OnDoorOpen();
		}
	}

	//DebugDraw();
}

void UDoorActorComponent::OnDebugToggled(IConsoleVariable* Var)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

//void UDoorActorComponent::DebugDraw()
//{
//	if (CVarToggleDebugDoor->GetBool())
//	{
//		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5f));
//		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
//		FString EnumAsString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
//		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 0.0f);
//	}
//}

void UDoorActorComponent::OnDoorOpen()
{
	DoorState = EDoorState::DS_Open;
	// This is not too great as we are having to scan for a general component to see if it exists. A door might not be an objective
	// 1. We don't check if the Objective is active technically.
	// 2. We could have multiple ObjectiveComponents on this DoorActor component that might not be related directly to this door open process.
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("DoorOpened"));
	//AAbstractionPlayerCharacter* PlayerCharacter = Cast<AAbstractionPlayerCharacter>(OtherActor);

	Cast<AInteractableDoor>(GetOwner())->OpenDoor();
	//OpenedEvent.Broadcast();
}

