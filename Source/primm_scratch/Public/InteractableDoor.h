// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableDoor.generated.h"

class UDoorActorComponent;

/**
 * 
 */
UCLASS()
class PRIMM_SCRATCH_API AInteractableDoor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AInteractableDoor();

protected:
	// NoClear to make sure the component is always set
	UPROPERTY(EditAnywhere, NoClear)
	UDoorActorComponent* DoorInteractionComponent;
};
