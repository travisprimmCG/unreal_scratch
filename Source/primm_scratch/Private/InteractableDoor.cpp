// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "DoorActorComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DoorInteractionComponent = CreateDefaultSubobject<UDoorActorComponent>(TEXT("DoorActorComponent"));
}