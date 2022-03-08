// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueRush.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABlueRush::ABlueRush()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RUSHEND"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_TeleCharge/P_Skill_Telecharge_Ice_Impact_02.P_Skill_Telecharge_Ice_Impact_02'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);
	InitialLifeSpan = 1.0f;
}

// Called when the game starts or when spawned
void ABlueRush::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlueRush::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

