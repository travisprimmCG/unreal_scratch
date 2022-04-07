// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "DoorActorComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DoorInteractionComponent = CreateDefaultSubobject<UDoorActorComponent>(TEXT("DoorInteractionComponent"));
	//if (DoorInteractionComponent->GetTriggerCapsule())
	//{
	//	DoorInteractionComponent->GetTriggerCapsule()->SetupAttachment(RootComponent);
	//}
}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();
	//DoorInteractionComponent->InteractionSuccess.AddDynamic(this, &AInteractableDoor::OnInteractionSuccess);
}

void AInteractableDoor::OpenDoor()
{
	//DoorInteractionComponent->OnDoorOpen();
	OnDoorOpen.Broadcast();
}

void AInteractableDoor::OnInteractionSuccess()
{
	OnDoorOpen.Broadcast();
}