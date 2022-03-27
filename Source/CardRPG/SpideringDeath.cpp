// Fill out your copyright notice in the Description page of Project Settings.


#include "SpideringDeath.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
ASpideringDeath::ASpideringDeath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ENEMYDEATH"));
	CollisionComp->InitBoxExtent(FVector(50.0f, 20.0f, 80.0f));
	RootComponent = CollisionComp;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ability/Summon/P_Summon_Child_Startup_large.P_Summon_Child_Startup_large'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	PSC->SetTemplate(PS.Object);
	PSC->SetupAttachment(CollisionComp);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDEFFECT"));
	AudioComponent->SetupAttachment(CollisionComp);

	static ConstructorHelpers::FObjectFinder<USoundBase> EF(TEXT("SoundWave'/Game/Resources/soundEffect/SE-34.SE-34'"));
	if (EF.Succeeded())
	{
		EffectSound = EF.Object;
	}

	UE_LOG(LogTemp, Warning, TEXT("EnemyDeath"));
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void ASpideringDeath::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->SetSound(EffectSound);
	AudioComponent->Play();
	
}

// Called every frame
void ASpideringDeath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

