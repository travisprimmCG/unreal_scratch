// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RockDamageActor.generated.h"

class UDealDamageComponent;
class UParticleSystemComponent;

UCLASS()
class PRIMM_SCRATCH_API ARockDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockDamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UDealDamageComponent* DealDamageComponent;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;
};
