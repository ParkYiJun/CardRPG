// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WALL"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_magicCircle1.P_ky_magicCircle1'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

