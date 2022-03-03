// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSkill.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWallSkill::AWallSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WALL"));
	CollisionComp->InitBoxExtent(FVector(50.0f,20.0f,50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireStorm.P_ky_fireStorm'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	PSC->SetFloatParameter("ALphaScale",0.5f);
	InitialLifeSpan=7.0f;
}

// Called when the game starts or when spawned
void AWallSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

