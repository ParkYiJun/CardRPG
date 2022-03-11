// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingSkill.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
// Sets default values
AMovingSkill::AMovingSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("MOVINGSKILL"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 50.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_Aura/P_AuraCircle_Ice_Base_01.P_AuraCircle_Ice_Base_01'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	InitialLifeSpan = 10.0f;
	MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called when the game starts or when spawned
void AMovingSkill::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(0.3,0.3,0.3));
	
}

// Called every frame
void AMovingSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Location = MainCharacter->GetActorLocation();
	FRotator Rotation = MainCharacter->GetActorRotation();

	SetActorLocation(Location+FVector(0,0,-88));
	SetActorRotation(Rotation);
}

