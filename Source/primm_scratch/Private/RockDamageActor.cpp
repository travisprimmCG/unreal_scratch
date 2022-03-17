// Fill out your copyright notice in the Description page of Project Settings.


#include "RockDamageActor.h"
#include "DealDamageComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ARockDamageActor::ARockDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DealDamageComponent = CreateDefaultSubobject<UDealDamageComponent>(TEXT("Deal Damage"));
	if (DealDamageComponent->GetTriggerCapsule())
	{
		RootComponent = DealDamageComponent->GetTriggerCapsule();
	}
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystemComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARockDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARockDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

