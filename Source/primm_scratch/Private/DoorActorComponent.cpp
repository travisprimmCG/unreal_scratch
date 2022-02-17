// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActorComponent.h"

// Sets default values for this component's properties
UDoorActorComponent::UDoorActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorActorComponent::BeginPlay()
{
	Super::BeginPlay();
	/*DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);
	DeltaRotation = DesiredRotation - GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;*/

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = StartRotation + DesiredRotation;

	CurrentRotationTime = 0.0f;

	//GetOwner()->SetActorRotation(DesiredRotation);

	// ...
	
}


// Called every frame
void UDoorActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentRotationTime < TimeToRotate)
	{
		CurrentRotationTime += DeltaTime;
		const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
	}


	/*FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (!CurrentRotation.Equals(FinalRotation, 5.0f))
	{
		CurrentRotation += DeltaRotation * DeltaTime;
		GetOwner()->SetActorRotation(CurrentRotation);
	}*/

	// ...
}

